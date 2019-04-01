from collections import namedtuple
from logging import basicConfig, warning, error
from os.path import getmtime, abspath, dirname, join
from datetime import datetime as dt
from sys import argv

from jinja2 import Environment, FileSystemLoader


basicConfig()

Enum = namedtuple('Enum', 'name fields underlying_type')


class Def(namedtuple('Definition', 'name read write address fields enums width')):
    @property
    def needs_constructor(self):
        if len(self.fields) > 1:
            return True
        if not self.fields:
            return False
        field = self.fields[0]
        return field.width <= 32


class Field(namedtuple('Field', 'name width offset enum')):
    @property
    def type(self):
        if self.enum:
            return self.enum.name

        if self.width == 1:
            return 'bool'

        for width in [32, 64]:
            if self.width <= width:
                return f'uint{width}_t'

    @property
    def mask(self):
        return hex(mask(self))


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
        TRIGGER = False

    class WriteOnly:
        WRITE = True
        TRIGGER = False

    class ReadWrite(ReadOnly, WriteOnly):
        pass

    class Trigger:
        READ = False
        WRITE = False
        TRIGGER = True

    def addr(address):
        class Address:
            ADDRESS = address
        return Address

    def width(w):
        class Width:
            WIDTH = w
        return Width

    globals_ = 'ReadOnly WriteOnly ReadWrite Address Trigger'.split()
    scope = dict(ReadOnly=ReadOnly, WriteOnly=WriteOnly, ReadWrite=ReadWrite, Trigger=Trigger,
                 Address=addr, Width=width)
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
        test_includes = local['TEST_INCLUDE']
    except KeyError:
        warning("no test include given, compiling the test will probably fail")
        test_includes = ''

    if not isinstance(test_includes, str):
        error("test include must be a str")
        exit()

    return namespace, dt.fromtimestamp(getmtime(file_name)), test_includes


def is_dunder(string):
    return string.startswith('__') and string.endswith('__')


def find_enum(cls):
    for key, value in cls.__dict__.items():
        if not is_dunder(key):
            fields = value.__dict__.copy()
            underlying_type = fields.pop('UNDERLYING_TYPE', None)
            yield Enum(key, {
                name: value for name, value in fields.items()
                if not is_dunder(name) and isinstance(value, int)
            }, underlying_type)


def cleanup_definitions(local):
    for key, value in list(local.items()):
        if not isinstance(value, type):
            continue

        if not hasattr(value, 'ADDRESS'):
            error(f"{key} has no 'Address'")
            continue
        address = getattr(value, 'ADDRESS')

        if not hasattr(value, 'READ') and not hasattr(value, 'WRITE'):
            error(f"{key} is neither readable nor writeable")
            continue
        read = getattr(value, 'READ', False)
        write = getattr(value, 'WRITE', False)

        fields = getattr(value, '__annotations__', {})

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
            cap = name.capitalize()

            matching_enum = None
            for enum in enums:
                if enum.name == cap:
                    matching_enum = enum
                    break

            fields_tuples.append(Field(name, width, offset, matching_enum))
            offset += width
        if offset == 0:
            offset = getattr(value, 'WIDTH')
        yield Def(key, bool(read), bool(write), int(address), fields_tuples, enums, offset)


def read_definition(file_name):
    scope, local, globals_ = prepare_scope()

    with open(file_name) as fin:
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


def main():
    if len(argv) != 2:
        print("usage: {} DEFINITION_FILE".format(argv[0]))
        exit(1)

    defs, meta = read_definition(argv[1])
    path = dirname(abspath(__file__))
    env = Environment(loader=FileSystemLoader(path))
    env.filters['hex'] = hex
    env.filters['bitand'] = int.__and__
    env.filters['cut'] = cut
    env.filters['mask'] = mask

    ns, datetime, test_include = meta
    test_values = [
        0,
        0xffffffffffffffff,
        0xaaaaaaaaaaaaaaaa,
        0x5555555555555555,
        0xcafedeadbabebeef
    ]

    base = argv[1][:-3]
    target = join(dirname(path), 'include', 'extoll', f'{base}_definitions.h')
    with open(target, 'w') as fout:
        template = env.get_template(f'{base}_definitions.h')
        fout.write(template.render(**locals()))

    target = join(dirname(path), 'tests', f'{base}_definitions.cpp')
    with open(target, 'w') as fout:
        template = env.get_template(f'{base}_definitions.cpp')
        fout.write(template.render(**locals()))


if __name__ == '__main__':
    main()
