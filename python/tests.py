from pytest import fixture


@fixture
def address():
    from pyhbp import Address
    return Address

def test_import_library():
    import pyhbp


def test_import_parts():
    from pyhbp import register_file
    from pyhbp import Address


def test_address_enum(address):
    print(address)
    print(dir(address))