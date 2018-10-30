#include "tests/switchram.h"

#include <random>
#include <limits>

#include <utility/rng.h>
#include <utility/watch.h>
#include <tests/switchram.h>


using namespace rf;
using namespace jtag;

SwitchRam::SwitchRam(HBP& hbp,RMA2_Nodeid node, uint8_t hicann)
    : TestBase(hbp), node(node), hicann_number(hicann) {}


void SwitchRam::run()
{
    auto fpga = hbp.fpga(node);
    auto jtag = hbp.jtag(node);
    auto rf = hbp.register_file(node);
    auto hicann = hbp.hicann(node, hicann_number);

    WATCH_STATUS_FROM(rf);
    WATCH_ERRORS_FROM(rf);

    fpga.reset();
    jtag.reset();

    fpga.configure_partner_host();

    rf.write<ArqTimings>({0x0c8, 0x32, 0x4, true});
    fpga.reset(Fpga::Reset::Arq);

    fpga.reset_set_only(Fpga::Reset::Arq);
    jtag.write<SystemEnable>(0);
    jtag.write<ArqRxTimeoutValue>((10 << 16) | 10);
    jtag.write<ArqTxTimeoutValue>((200 << 16) | 200);

    jtag.write<ArqControl>((1 << 16) | 1);
    jtag.write<ArqControl>(0);
    fpga.reset_set_only(Fpga::Reset::None);



    jtag.write<SystemEnable>(0);
    jtag.write<SystemEnable>(1);
    jtag.trigger<StopLink>();
    jtag.write<LinkControl>(0x61);
    jtag.trigger<StopLink>();
    jtag.trigger<StartLink>();
    usleep(90000);

    for (uint16_t i = 0; i < 111; ++i)
    {
        hicann.write(i, 0xc0fecafe);
    }
    hicann.clear_all();

    for (uint16_t i = 0; i < 111; ++i)
    {
        hicann.read(0);
    }
    hicann.diff_all();

    /*
    std::vector<uint16_t> test_data;
    {
        Rng<uint16_t> rng(1, Rng<uint16_t>::max, 0);

        const uint16_t START_ADDRESS = 0;
        const uint16_t END_ADDRESS = 111;

        for (uint16_t address = START_ADDRESS; address <= END_ADDRESS; ++address)
        {
            auto number = rng.roll();
            test_data.push_back(number);
            // TODO: somehow send this shit: address, number
        }
    }
    */

}
