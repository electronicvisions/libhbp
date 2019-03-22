from argparse import ArgumentParser
from collections import namedtuple
from logging import basicConfig, warning, error
from sys import stdout
from os.path import getmtime, abspath, dirname
from datetime import datetime

from jinja2 import Environment, FileSystemLoader


basicConfig()

Enum = namedtuple('Enum', 'name fields')
Def = namedtuple('Definition', 'name read write address fields enums width')


class Field(namedtuple('Field', 'name width offset')):
    @property
    def type(self):
        return 'bool' if self.width == 1 else 'uint64_t'


def mask(field_or_def):
    return (2 << (field_or_def.width - 1)) - 1


def cut(field_or_def, value):
    value >>= getattr(field_or_def, 'offset', 0)
    value &= mask(field_or_def)

    if field_or_def.width == 1:
        return str(bool(value)).lower()
    return hex(value)


def prepare_scope():
    class ReadOnly:
        READ = True

    class WriteOnly:
        WRITE = True

    class ReadWrite(ReadOnly, WriteOnly):
        pass

    def addr(address):
        class Address:
            ADDRESS = address

        return Address

    globals_ = 'ReadOnly WriteOnly ReadWrite Address'.split()
    scope = dict(ReadOnly=ReadOnly, WriteOnly=WriteOnly, ReadWrite=ReadWrite, Address=addr)
    local = {}

    return scope, local, globals_


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

        fields_tuples = []
        offset = 0
        for name, width in fields.items():
            fields_tuples.append(Field(name, width, offset))
            offset += width
        yield Def(key, bool(read), bool(write), int(address), fields_tuples, enums, offset)


def read_definition(file_name):
    scope, local, globals_ = prepare_scope()

    with open('hbp.py') as fin:
        exec(fin.read(), scope, local)

    definitions = list(cleanup_definitions(local))

    no_duplicate_dict = {}
    for d in definitions:
        if d.address in no_duplicate_dict:
            dup = no_duplicate_dict[d.address]
            raise RuntimeError(f"{d.name} and {dup.name} have the same address: {d.address}")
        else:
            no_duplicate_dict[d.address] = d

    meta = read_meta(file_name, local)
    return definitions, meta


parser = ArgumentParser("generate header files for register file definitions.")
parser.add_argument('file_name', metavar='DEFINITIONS',
                    help="the file that contains the register file definitions")
parser.add_argument('-o', '--out',
                    default=stdout.fileno(),
                    help="the file to write into (default is stdout)")
parser.add_argument('-t', '--test', default=False, action='store_true',
                    help="generate tests instead of definitions")

if __name__ == '__main__':
    argv = parser.parse_args()

    defs, meta = read_definition(argv.file_name)
    path = dirname(abspath(__file__))
    env = Environment(loader=FileSystemLoader(path))
    env.filters['hex'] = hex
    env.filters['bitand'] = int.__and__
    env.filters['cut'] = cut
    env.filters['mask'] = mask

    with open(argv.out, 'w', closefd=argv.out != stdout.fileno()) as fout:
        def write(*args, **kwargs):
            print(*args, file=fout, **kwargs)


        template = env.get_template('test.cpp' if argv.test else 'definition.h')
        rendered = template.render(
            defs=defs,
            ns=meta[0],
            datetime=meta[1],
            test_include=meta[2],
            test_values=[
                0,
                0xffffffffffffffff,
                0xaaaaaaaaaaaaaaaa,
                0x5555555555555555,
                0xcafedeadbabebeef
            ]
        )
        fout.write(rendered)
