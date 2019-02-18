#include "util.h"

using namespace extoll::library;
using namespace extoll::library::rf;
using namespace extoll::library::jtag;
using extoll::library::Fpga;


void highspeed_init(RegisterFile& rf, JTag& jtag, Fpga& fpga, uint8_t hicann)
{
	fpga.reset(Fpga::Reset::All);

	rf.write<HicannChannel>({hicann & 7u});

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
	CAPTURE(node);
	auto rf = EX.register_file(node);
	auto j = EX.jtag(node);
	auto fpga = EX.fpga(node);

	FOR_EACH_HICANN {
		DYNAMIC_SECTION("hicann is " << int(hicann))
		{
			highspeed_init(rf, j, fpga, hicann);
			auto hicann_status = j.read<Status>(hicann) & 0x49;
			auto fpga_status = rf.read<HicannIfState>().raw & 0x49;

			CHECK(hicann_status == 0x49);
			CHECK(fpga_status == 0x49);
		}
	}
}

TEST_CASE("Highspeed transmission via JTAG from FPAG to HICANN", "[hs]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);
	auto rf = EX.register_file(node);
	auto j = EX.jtag(node);
	auto fpga = EX.fpga(node);

	FOR_EACH_HICANN {
		DYNAMIC_SECTION("hicann is " << int(hicann))
		{
			highspeed_init(rf, j, fpga, hicann);

			j.write<TestControl>(1, hicann);
			rf.write<HicannChannel>({hicann & 7u});
			rf.write<HicannPacketGen>({0, 0, false});

			for (int i = 0; i < 10; ++i)
			{
				uint64_t sent = 0x1234ull << (i % 8);
				rf.write<HicannIfTxData>({sent});
				rf.write<HicannIfControls>({false, true, false, false, false});

				usleep(1000);

				uint64_t received = j.read<RxData>(hicann) & 0xffffff;
				CHECK(sent == received);
			}
		}
	}
}

TEST_CASE("Highspeed transmission via JTAG from HICANN to FPGA", "[hs][!shouldfail]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);
	auto rf = EX.register_file(node);
	auto j = EX.jtag(node);
	auto fpga = EX.fpga(node);

	FOR_EACH_HICANN {
		DYNAMIC_SECTION("hicann is " << int(hicann))
		{
			highspeed_init(rf, j, fpga, hicann);

			j.write<TestControl>(1, hicann);
			rf.write<HicannChannel>({hicann & 7u});
			rf.write<HicannPacketGen>({0, 0, false});

			for (int i = 0; i < 10; ++i)
			{
				uint64_t sent = 0xfedcba98ull << (i %32);
				j.write<TxData>(sent, hicann);
				j.trigger<StartConfigPackage>(hicann);

				usleep(1000);

				uint64_t received = rf.read<HicannIfRxConfig>().data;
				CHECK(sent == received);
			}
		}
	}
}
