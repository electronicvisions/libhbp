#include "application_protocol.h"

using namespace extoll::library;
using namespace extoll::library::rf;
using namespace extoll::library::jtag;

uint8_t dnc_index(extoll::library::JTag& jtag, uint8_t hicann)
{
    return (jtag.active_hicanns() - 1 - hicann) & 7u;
}


void highspeed_init(RegisterFile& rf, JTag& jtag, Fpga& fpga, uint8_t hicann)
{
    fpga.reset_set_only(Fpga::Reset::Arq);
    rf.write<HicannChannel>({dnc_index(jtag, hicann) & 7u});

    HicannIfConfig stop;
    stop.raw = 0x4000c;
    rf.write<HicannIfConfig>(std::move(stop));
    jtag.trigger<StopLink>(hicann);

    usleep(20);
    jtag.write<LinkControl>(0x061, hicann);
    jtag.write<LvdsPadsEnable>(0, hicann);
    jtag.trigger<StartLink>(hicann);
    HicannIfConfig start;
    start.raw = 0x4000d;
    rf.write<HicannIfConfig>(std::move(start));

    fpga.reset_set_only(Fpga::Reset::None);
    usleep(10000);
}


HsStatus highspeed_status(RegisterFile& rf, JTag& jtag, uint8_t hicann)
{
    return {
            (rf.read<HicannIfState>().raw & 0x49u) == 0x49,
            (jtag.read<Status>(hicann & 7u) & 0x49u) == 0x49
    };
}

std::ostream& operator<<(std::ostream& out, const HsStatus& status)
{
    return out << std::boolalpha << "fpga-ok=" << status.fpga_ok << ", hicann-ok=" << status.hicann_ok;
}
