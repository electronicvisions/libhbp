#include "util.h"

#define EX Extoll::Instance()
#define FOR_EACH_HICANN for (uint8_t hicann = 0; hicann < j.active_hicanns(); ++hicann)

using namespace extoll::library;
using namespace extoll::library::rf;
using namespace extoll::library::jtag;
using extoll::library::Fpga;


void highspeed_init(RegisterFile& rf, JTag& jtag, Fpga& fpga, uint8_t hicann)
{
	fpga.reset(Fpga::Reset::All);

	rf.write<HicannChannel>({hicann});

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

	usleep(10000);
}


TEST_CASE("Highspeed Init succeeds", "[hs]")
{
	auto node = GENERATE(hicann_nodes());

	auto rf = EX.register_file(node);
	auto j = EX.jtag(node);
	auto fpga = EX.fpga(node);

	FOR_EACH_HICANN {
		DYNAMIC_SECTION("node is " << node << " hicann is " << int(hicann))
		{
			highspeed_init(rf, j, fpga, hicann);
			auto hicann_status = j.read<Status>(hicann) & 0x49;
			auto fpga_status = rf.read<HicannIfState>().raw & 0x49;

			CHECK(hicann_status == 0x49);
			CHECK(fpga_status == 0x49);
		}
	}
}

TEST_CASE("Highspeed transmission via JTAG from FPAG to HICANN works", "[hs]")
{
	auto node = GENERATE(hicann_nodes());

	auto rf = EX.register_file(node);
	auto j = EX.jtag(node);
	auto fpga = EX.fpga(node);

	FOR_EACH_HICANN {
		DYNAMIC_SECTION("node is " << node << " hicann is " << int(hicann))
		{
			highspeed_init(rf, j, fpga, hicann);

			j.write<TestControl>(1, hicann);
			rf.write<HicannChannel>({hicann});
			rf.write<HicannPacketGen>({0, 0, false});

			for (int i = 0; i < 100; ++i)
			{
				uint64_t sent = 0x1234 << (i % 8);
				rf.write<HicannIfTxData>({sent});
				rf.write<HicannIfControls>({false, true, false, false, false});

				usleep(1000);

				uint64_t received = j.read<RxData>(hicann) & 0xffffff;

				CHECK(received == sent);
			}
		}
	}
}