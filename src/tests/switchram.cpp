#include "tests/switchram.h"

#include <random>
#include <limits>

#include <utility/rng.h>
#include <utility/watch.h>

using namespace rf;

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

    rf.write<ArqTimings>({0x0c8, 0x32, 0x4, true});
    fpga.reset(Fpga::Reset::Arq);

    fpga.reset_set_only(Fpga::Reset::Arq);
    jtag.write(jtag::SystemEnable, 0);
    jtag.write(jtag::ArqRxTimeoutValue, (10 << 16) | 10);
    jtag.write(jtag::ArqTxTimeoutValue, (200 << 16) | 200);

    jtag.write(jtag::ArqControl, (1 << 16) | 1);
    jtag.write(jtag::ArqControl, 0);
    fpga.reset_set_only(Fpga::Reset::None);

    jtag.write(jtag::SystemEnable, 0);
    jtag.write(jtag::SystemEnable, 1);
    jtag.trigger(jtag::StopLink);
    jtag.write(jtag::LinkControl, 0x61);
    jtag.trigger(jtag::StopLink);
    jtag.trigger(jtag::StartLink);
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

    std::cout << "IRRA " << rf.read(0x1078) << "\n";

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
