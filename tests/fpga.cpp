#include "helper/util.h"
#include "helper/application_protocol.h"

using extoll::library::Fpga;
using namespace extoll::library::rf;
using namespace extoll::library::jtag;


const uint32_t ARQ_LOOPBACK = 0x20002;

union Config
{
    struct
    {
        uint64_t data : 32;
        uint64_t address : 16;
        bool write : 1;
        bool tag : 1;
        uint64_t unused : 9;
        uint64_t hicann : 3;
    } parts;
    uint64_t raw = 0;
};

TEST_CASE("FPGA Config receives answer", "[fpga]")
{
    auto node = GENERATE(hicann_nodes());
    CAPTURE(node);
    auto rf = EX.register_file(node);
    auto fpga = EX.fpga(node);
    auto j = EX.jtag(node);

    fpga.reset();

    FOR_EACH_HICANN
    {
        highspeed_init(rf, j, fpga, hicann);
        auto status = highspeed_status(rf, j, hicann);
        REQUIRE(status.fpga_ok);
        REQUIRE(status.hicann_ok);


        fpga.configure_partner_host();

        j.write<ArqControl>(ARQ_LOOPBACK, hicann);
    };

    usleep(100000);

    FOR_EACH_HICANN
    {
        auto hc = EX.hicann(node, int8_t(hicann & 0x7));
        hc.clear_all();

        Config config;

        for (int write = 0; write < 2; ++write)
        {
            for (int tag = 0; tag < 2; ++tag)
            {
                for (uint8_t h = 0; h < 2; ++h)
                {
                    config.parts = {
                            0xcafe, 0xaf, write>0, tag>0, 0, h & 0x7u
                    };
                    hc.send(config.raw);
                }
            }
        }

        usleep(100000);
        rf.probe();
        hc.diff_all();
    };

}