#include <tests/jtagrw.h>

#include <bitset>

JtagRw::JtagRw(HBP& hbp, RMA2_Nodeid node, uint8_t hicann)
    : TestBase(hbp), node(node), hicann_number(hicann) {}

void JtagRw::run()
{
    auto fpga = hbp.fpga(node);
    auto jtag = hbp.jtag(node);
    auto rf = hbp.register_file(node);

    fpga.configure_partner_host();

    auto id = jtag.read(jtag::ID);

    std::cout << "JTAG ID: 0x" << std::hex << id << "\n";

    jtag.set_bypass();
    std::bitset<64> data(0xffffffffffffffff);
    auto r = jtag.shift_through(data, 32);
    auto r2 = jtag.shift_through<64>("1111011011", 10);

    std::cout << r << "\n";
    std::cout << r2 << "\n";
}

