#include "util.h"

using namespace extoll::library;
using namespace extoll::library::rf;
using namespace extoll::library::jtag;
using extoll::library::Fpga;


void highspeed_init(RegisterFile& rf, JTag& jtag, Fpga& fpga, uint8_t hicann)
{
	fpga.reset(Fpga::Reset::All);

	auto dnc_index = jtag.active_hicanns() - 1 - hicann;
	rf.write<HicannChannel>({dnc_index & 7u});

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

struct HsStatus
{
	bool fpga_ok;
	bool hicann_ok;
};

std::ostream& operator<<(std::ostream& out, const HsStatus& status)
{
	return out << std::boolalpha << "fpga-ok=" << status.fpga_ok << ", hicann-ok=" << status.hicann_ok;
}

HsStatus highspeed_status(RegisterFile& rf, JTag& jtag, uint8_t hicann)
{
	return {
		(rf.read<HicannIfState>().raw & 0x49) == 0x49,
		(jtag.read<Status>(hicann & 7u) & 0x49) == 0x49
	};
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
			auto status = highspeed_status(rf, j, hicann);

			REQUIRE(status.fpga_ok);
			REQUIRE(status.hicann_ok);
		}
	}
}

TEST_CASE("Highspeed transmission via JTAG from FPGA to HICANN", "[hs]")
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
			CAPTURE(highspeed_status(rf, j, hicann));

			j.write<TestControl>(1, hicann);
            auto dnc_index = j.active_hicanns() - 1 - hicann;
			rf.write<HicannChannel>({dnc_index & 7u});
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

TEST_CASE("Highspeed transmission via JTAG from HICANN to FPGA", "[hs]")
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
			CAPTURE(highspeed_status(rf, j, hicann));

			j.write<TestControl>(1, hicann);
            auto dnc_index = j.active_hicanns() - 1 - hicann;
			rf.write<HicannChannel>({dnc_index & 7u});
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
