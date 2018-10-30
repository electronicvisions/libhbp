#include <tests/jtagrw.h>

#include <bitset>

JtagRw::JtagRw(HBP& hbp, RMA2_Nodeid node, uint8_t hicann)
    : TestBase(hbp), node(node), hicann_number(hicann) {}

using namespace jtag;

void JtagRw::run()
{
    auto fpga = hbp.fpga(node);
    auto jtag = hbp.jtag(node);

    fpga.reset();
    jtag.reset();
    fpga.configure_partner_host();

    auto id = jtag.read<ID>();

    std::cout << "JTAG ID: 0x" << std::hex << id << "\n";

    std::cout << "IBIAS  : 0x" << jtag.write<IBias>(0x27) << "\n";
    std::cout << "IBIAS  : 0x" << jtag.write<IBias>(0x27) << "\n";
}

