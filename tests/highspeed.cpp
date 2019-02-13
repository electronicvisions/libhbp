#include "util.h"

#define EX Extoll::Instance()
#define FOR_EACH_HICANN for (uint8_t hicann = 0; hicann < j.active_hicanns(); ++hicann)

using namespace extoll::library::rf;
using namespace extoll::library::jtag;
using extoll::library::Fpga;


TEST_CASE("Highspeed Init", "[hs]")
{
	for (auto node : NodesWithHicanns)
	{
		auto rf = EX.register_file(node);
		auto j = EX.jtag(node);
		auto fpga = EX.fpga(node);

		FOR_EACH_HICANN {
			DYNAMIC_SECTION("node is " << node << " hicann is " << int(hicann))
			{
				fpga.reset(Fpga::Reset::All);

				rf.write<HicannChannel>({hicann});
				CHECK(j.read<ID>(hicann) == 0x14849434);

				HicannIfConfig stop;
				stop.raw = 0x4000c;
				rf.write<HicannIfConfig>(std::move(stop));
				j.trigger<StopLink>(hicann);

				auto fpga_status = rf.read<HicannIfState>().raw & 0x49;

				usleep(20);
				j.write<LinkControl>(0x061, hicann);
				j.write<LvdsPadsEnable>(0, hicann);
				j.trigger<StartLink>(hicann);
				HicannIfConfig start;
				start.raw = 0x4000d;
				rf.write<HicannIfConfig>(std::move(start));

				usleep(10000);
				auto hicann_status = j.read<Status>(hicann) & 0x49;
				fpga_status = rf.read<HicannIfState>().raw & 0x49;

				CHECK(hicann_status == 0x49);
				CHECK(fpga_status == 0x49);
			}
		}

	}
}
