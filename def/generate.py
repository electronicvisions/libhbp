from argparse import ArgumentParser
from collections import namedtuple
from logging import basicConfig, warning, error
from sys import stdout
from os.path import getmtime
from datetime import datetime


basicConfig()

Enum = namedtuple('Enum', 'name fields')
Field = namedtuple('Field', 'name width')
Def = namedtuple('Definition', 'name read write address fields enums')


def prepare_scope():
    class ReadOnly:
        READ = True


    class WriteOnly:
        WRITE = True


    class ReadWrite(ReadOnly, WriteOnly):
        pass


    def Address(address):
        class Address:
            pass
        Address.ADDRESS = address
        return Address

    GLOBALS = 'ReadOnly WriteOnly ReadWrite Address'.split()
    scope = dict(ReadOnly=ReadOnly, WriteOnly=WriteOnly, ReadWrite=ReadWrite, Address=Address)
    local = {}

    return scope, local, GLOBALS


def read_meta(file_name, local):
    try:
        namespace = local['NAMESPACE']
    except KeyError:
        warning("no namespace given, defaulting to empty namespace")
        namespace = ()

    if isinstance(namespace, str):
        namespace = [namespace]

    if not isinstance(namespace, (tuple, list)):
        error("namespace must be a str, list or tuple, defaulting to empty namespace")
        namespace = ()

    if not all(part.isidentifier() for part in namespace):
        error("namespace parts must be valid identifiert, defaulting to empty namespace")
        namespace = ()

    try:
        test_include = local['TEST_INCLUDE']
    except KeyError:
        warning("no test include given, compiling the test will probably fail")
        test_include = ''

    if not isinstance(test_include, str):
        error("test include must be a str")
        exit()

    return namespace, datetime.fromtimestamp(getmtime(file_name)), test_include


def is_dunder(string):
    return string.startswith('__') and string.endswith('__')


def find_enum(cls):
    for key, value in cls.__dict__.items():
        if not is_dunder(key):
            yield Enum(key, {
                name: value for name, value in value.__dict__.items()
                    if not is_dunder(name) and isinstance(value, int)
            })


def cleanup_definitions(local):
    for key, value in list(local.items()):
        if not isinstance(value, type):
            continue

        if not hasattr(value, 'ADDRESS'):
            error(f"{key} has no 'Address'")
            continue
        address = value.ADDRESS

        if not hasattr(value, 'READ') and not hasattr(value, 'WRITE'):
            error(f"{key} is neither readable nor writeable")
            continue
        read = getattr(value, 'READ', False)
        write = getattr(value, 'WRITE', False)

        if not getattr(value, '__annotations__', None):
            error(f"{key} has not field definitions")
            continue
        fields = value.__annotations__

        if not all(isinstance(width, int) for width in fields.values()):
            error(f"{key}: field widths must be integers")
            continue
        if sum(fields.values()) > 64:
            error(f"{key}: total field width may not exceed 64")
            continue

        enums = list(find_enum(value))

        fields = [Field(name, width) for name, width in fields.items()]

        yield Def(key, bool(read), bool(write), int(address), fields, enums)


def read_definition(file_name):
    scope, local, GLOBALS = prepare_scope()

    with open('hbp.py') as fin:
        exec(fin.read(), scope, local)

    definitions = list(cleanup_definitions(local))
    meta = read_meta(file_name, local)
    return definitions, meta


def print_definition(d, write):
    write(f'struct {d.name} {{')

    write('    union {')
    write(f'        struct {{')
    for field in d.fields:
        type = 'bool' if field.width == 1 else 'uint64_t'
        write(f'            {type} {field.name}: {field.width};')
    write('        };')
    write('        uint64_t raw;')
    write('    };')

    write()
    for enum in d.enums:
        write(f'    enum {enum.name} {{')
        for field, value in enum.fields.items():
            write(f'        {field} = {value},')
        write('    };')

    ft = 'false', 'true'
    write(f'    const static RMA2_NLA ADDRESS = 0x{d.address:x};')
    write(f'    const static bool READABLE = {ft[d.read]};')
    write(f'    const static bool WRITABLE = {ft[d.write]};')

    write('};')

    write(f'static_assert(sizeof({d.name}) == sizeof(uint64_t)', end='')
    write(f', "sizeof register file {d.name!r} != sizeof uint64_t");')
    write(f'static_assert(std::is_trivial<{d.name}>::value', end='')
    write(f', "{d.name!r} is not trivial");')
    write()


def print_warning(write, time):
    write("/**\n * This is a generated file - do not change it")
    write(" *", time.strftime('%d.%m.%Y %H:%M:%S.%f'), "\n */\n")


def print_all(defs, write, meta):
    namespace, time, _ = meta

    print_warning(write, time)

    write('#pragma once')
    write()
    write('#include <cinttypes>')
    write()
    write('#include <extoll/rma.h>')
    write()
    write()

    for part in namespace:
        write(f'namespace {part} {{')
    write()

    write('#pragma GCC diagnostic push')
    write('#pragma GCC diagnostic ignored "-Wpedantic"')
    for d in defs:
        print_definition(d, write)
    write('#pragma GCC diagnostic pop')

    write('}' * len(namespace))


TEST_VALUES = [
    0,
    0xffffffffffffffff,
    0xaaaaaaaaaaaaaaaa,
    0x5555555555555555,
    0xcafedeadbabebeef
]


def print_test_section(d):
    write(f'TEST_CASE("Generated definition {d.name!r}", "[definitions]")\n{{')

    write(f'    SECTION("write raw - read fields")\n    {{')
    write(f'        {d.name} rf;')
    for value in TEST_VALUES:
        write(f'\n        rf.raw = 0x{value:x};')
        write()

        offset = 0
        binary = f'{value:064b}'[::-1]
        for f in d.fields:
            pattern = binary[offset:offset + f.width][::-1]
            expected = int(pattern, 2)
            offset += f.width

            write(f'        CHECK(rf.{f.name} == 0x{expected:x});')
    write('    }')

    write(f'\n    SECTION("write fields - read raw")\n    {{')
    write(f'        {d.name} rf;')
    for value in TEST_VALUES:
        write()
        offset = 0
        binary = f'{value:064b}'[::-1]
        for f in d.fields:
            pattern = binary[offset:offset + f.width][::-1]
            expected = int(pattern, 2)
            offset += f.width

            write(f'        rf.{f.name} = 0x{expected:x};')
        raw = int(binary[:offset][::-1], 2)
        mask = (2 ** offset) - 1
        write(f'\n        REQUIRE((rf.raw & 0x{mask:x}) == 0x{raw:x});')
    write('    }')

    write('}')


def print_tests(defs, write, meta):
    namespace, time, test_include = meta

    print_warning(write, time)

    write('#include <catch.hpp>')
    write(f'#include {test_include}\n\n')

    namespace = '::'.join(namespace)
    write(f'using namespace {namespace};\n')

    for d in defs:
        print_test_section(d);


parser = ArgumentParser("generate header files for register file definitions.")
parser.add_argument('file_name', metavar='DEFINITIONS',
    help="the file that contains the register file definitions")
parser.add_argument('-o', '--out',
    default=stdout.fileno(),
    help="the file to write into (default is stdout)")
parser.add_argument('-t', '--test', default=False, action='store_true',
    help="generate tests instead of definitions")


if __name__ == '__main__':
    args = parser.parse_args()

    defs, meta = read_definition(args.file_name)

    with open(args.out, 'w', closefd=args.out != stdout.fileno()) as fout:
        def write(*args, **kwargs):
            print(*args, file=fout, **kwargs)

        if args.test:
            print_tests(defs, write, meta)
        else:
            print_all(defs, write, meta)
