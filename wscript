NAME = 'extoll-hbp-lib-{}'.format


def options(opt):
    opt.load('compiler_c')
    opt.load('compiler_cxx')


def configure(cfg):
    cfg.load('compiler_c')
    cfg.load('compiler_cxx')
    cfg.check_cc(header_name='rma2.h', uselib_store='RMA2')
    cfg.check_cc(lib='rma2', uselib_store='RMA2')
    cfg.check_cc(lib='dl')
    cfg.check_cc(lib='rma2rc', use='DL RMA2')
    cfg.check_cxx(header_name = "catch2/catch.hpp")


def build(bld):
    bld.program(
        source='scratch.cpp',
        target='scratch',
        name=NAME('scratch')
    )

    lib_src = '''
    buffer connection exception extoll fpga hicann jtag
    register_file rma
    '''.split()
    lib_src = ['src/{}.cpp'.format(file) for file in lib_src]
    bld.shlib(
        source=lib_src,
        target='hbpextoll',
        name=NAME('shared'),
        includes='include',
        export_includes='include',
        use='RMA2 RMA2RC DL'
    )

