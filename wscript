from waflib.extras.test_base import summary

def depends(dep):
    dep('librma')


def options(opt):
    opt.load('compiler_c')
    opt.load('compiler_cxx')
    opt.load('gtest')


def configure(cfg):
    cfg.load('compiler_c')
    cfg.load('compiler_cxx')
    cfg.load('gtest')
    cfg.check_cxx(header_name = "catch2/catch.hpp")


def build(bld):
    bld(target          = 'libhbp_inc',
        export_includes = ['include', 'external'],
    )

    bld.program(
        source='scratch.cpp',
        target='libhbp-scratch',
    )

    bld.shlib(
        target       = 'rma',
        features     = 'cxx',
        source       = ['src/buffer.cpp',
                        'src/register_file.cpp',
                        'src/connection.cpp',
                        'src/extoll.cpp',
                        'src/rma.cpp',
                        'src/jtag.cpp',
                        'src/fpga.cpp',
                        'src/exception.cpp',
                        'src/hicann.cpp',
                        'src/notification_poller.cpp',
                       ],
        use          = ['rma2rc', 'rma2', 'libhbp_inc'],
        cxxflags     = '-pthread',
        lib          = 'pthread',
        install_path = '${PREFIX}/lib',
    )

    bld.program(
        target = 'libhbp-tests',
        features = 'cxx',
        source = [
            'tests/run.cpp',
            'tests/helper/util.cpp',
            'tests/rra.cpp',
            'tests/jtag.cpp',
            'tests/if.cpp',
            'tests/rf_definitions.cpp',
            'tests/highspeed.cpp',
            'tests/slowspeed.cpp',
            'tests/fpga.cpp',
            'tests/helper/application_protocol.cpp',
            'tests/anything_unused.cpp'
        ],
        cxxflags     = '-pthread',
        lib          = 'pthread',
        use = ['libhbp_inc', 'librma_inc', 'PMAP4RMA2', 'rma'],
    )

    for ex in 'main minimal al'.split():
        bld.program(
            target = 'libhbp-{}'.format(ex),
            features = 'cxx',
            source = ['src/{}.cpp'.format(ex)],
            use = ['rma', 'rma2rc', 'rma2', 'libhbp_inc', 'librma_inc'],
        )

    bld.program(
        target = 'libhbp-kill',
        features = 'cxx',
        source = ['src/kill.cpp'],
        use = ['libhbp_inc', 'librma_inc', 'DL4RMA2', 'PMAP4RMA2', 'rma2'],
    )

    bld.add_post_fun(summary)
