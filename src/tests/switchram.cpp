#include "tests/switchram.h"

#include <random>
#include <limits>

#include <utility/rng.h>

using namespace rf;

SwitchRam::SwitchRam(HBP& hbp,RMA2_Nodeid node)
    : TestBase(hbp), node(node) {}


void SwitchRam::run()
{
    auto fpga = hbp.fpga(node);
    auto jtag = hbp.jtag(node);
    auto rf = hbp.register_file(node);

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


}
