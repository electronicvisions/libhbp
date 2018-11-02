#include <tests/jtagrw.h>

#include <bitset>

JtagRw::JtagRw(Extoll& hbp, RMA2_Nodeid node, uint8_t hicann)
    : TestBase(hbp), node(node), hicann_number(hicann) {}

using namespace jtag;
using namespace rf;

void JtagRw::run()
{
    auto jtag = hbp.jtag(node);

    jtag.reset();

    auto id = jtag.read<ID>();
    critical<uint64_t>("jtag id", 0x14849434, id);

    jtag.write<IBias>(0x28);
    auto ibias = jtag.write<IBias>(0x28);
    critical<uint64_t>("scratch test", 0x28, ibias);
}

