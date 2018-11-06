from __future__ import print_function

from os import environ
from os.path import join


NAME = 'extoll-hbp-lib-{}'.format

def options(opt):
    opt.load('compiler_cxx')


def configure(cfg):
    cfg.env.CXX = environ.get('CXX', cfg.env.CXX)
    cfg.load('compiler_cxx')

    try:
        extoll_home = environ['EXTOLL_R2_HOME']
    except KeyError:
        cfg.fatal("$EXTOLL_R2_HOME must be set")

    lib_path = join(extoll_home, 'lib')
    cfg.find_file('librma2.so', lib_path)
    cfg.find_file('librma2rc.so', lib_path)

    cfg.env.INCLUDES_RMA = join(extoll_home, 'include')
    cfg.find_file('rma2.h', cfg.env.INCLUDES_RMA)
    cfg.env.LIB_RMA = 'rma2'
    cfg.env.LIBPATH_RMA = lib_path

    cfg.env.INCLUDES_RMARC = join(extoll_home, 'include')
    cfg.env.LIB_RMARC = 'rma2rc'
    cfg.env.LIBPATH_RMARC = lib_path

    cfg.env.LIB_DL = 'dl'



def build(bld):
    bld.program(
        source='scratch.cpp',
        target='scratch',
        name=NAME('scratch')
        )

    lib_src = '''
    buffer connection exception extoll fpga hicann jtag
    register_file register_files rma
    '''.split()
    lib_src = ['src/{}.cpp'.format(file) for file in lib_src]
    bld.shlib(
        source=lib_src,
        target='hbpextoll',
        name=NAME('shared'),
        includes=['include'],
        use='RMA RMARC DL'
    )

    test_src = 'jtagrw register_file switchram test'.split()
    test_src = ['src/tests/{}.cpp'.format(file) for file in test_src]
    test_src.append('src/main.cpp')
    bld.program(
        source=test_src + lib_src,
        target='extoll-test',
        name=NAME('test'),
        use=NAME('shared'),
        includes=['include']
    )
