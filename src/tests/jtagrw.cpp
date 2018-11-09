#include <tests/jtagrw.h>

#include <bitset>


JtagRw::JtagRw(extoll::library::Extoll& hbp, RMA2_Nodeid node, uint8_t hicann)
    : TestBase(hbp), node(node), hicann_number(hicann) {}

void JtagRw::run()
{
    namespace rf = extoll::library::rf;
    namespace cmd = extoll::library::jtag;
    auto jtag = hbp.jtag(node);

    jtag.reset();

    auto id = jtag.read<cmd::ID>();
    critical<uint64_t>("jtag id", 0x14849434, id);

    jtag.write<cmd::IBias>(0x28);
    auto ibias = jtag.write<cmd::IBias>(0x28);
    critical<uint64_t>("scratch test", 0x28, ibias);

    jtag.read<cmd::ID>();
    std::cout << "Status: " << std::hex << jtag.read<cmd::Status>() << "\n";
    jtag.read<cmd::ID>();

    jtag.set_command(0x1a);
    std::cin.get();
    std::cout << "Data: " << std::hex << jtag.get_data(8) << "\n";
}
