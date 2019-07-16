#include "helper/util.h"
#include "helper/application_protocol.h"

using namespace extoll::library::rf;
using namespace extoll::library::jtag;
using extoll::library::Fpga;


TEST_CASE("Highspeed Init succeeds", "[hs]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);
	auto rf = EX.register_file(node);
	auto j = EX.jtag(node);
	auto fpga = EX.fpga(node);

	FOR_EACH_HICANN {
        CAPTURE(hicann);
	    highspeed_init(rf, j, fpga, hicann);
		auto status = highspeed_status(rf, j, hicann);

		REQUIRE(status.fpga_ok);
		REQUIRE(status.hicann_ok);
	}
}

TEST_CASE("Highspeed transmission via JTAG from Fpga to Hicann", "[hs]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);
	auto rf = EX.register_file(node);
	auto j = EX.jtag(node);
	auto fpga = EX.fpga(node);

	FOR_EACH_HICANN {
	    highspeed_init(rf, j, fpga, hicann);
		CAPTURE(highspeed_status(rf, j, hicann));
		CAPTURE(hicann);

		j.write<TestControl>(1, hicann);
		rf.write<HicannChannel>({dnc_index(j, hicann) & 7u});
		rf.write<HicannPacketGen>({0, false, false});

		for (size_t i = 0; i < 10; ++i)
		{
			uint64_t sent = 0x1234ull << (i % 8u);
			rf.write<HicannIfTxData>({sent});
			rf.write<HicannIfControls>({false, true, false, false, false});

			usleep(1000);

			uint64_t received = j.read<RxData>(hicann) & 0xffffffu;
			CHECK(sent == received);
		}
	}
}

TEST_CASE("Highspeed transmission via JTAG from Hicann to Fpga", "[hs]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);
	auto rf = EX.register_file(node);
	auto j = EX.jtag(node);
	auto fpga = EX.fpga(node);

	FOR_EACH_HICANN {
	    highspeed_init(rf, j, fpga, hicann);
		CAPTURE(highspeed_status(rf, j, hicann));
		CAPTURE(hicann);

		j.write<TestControl>(1, hicann);
		rf.write<HicannChannel>({dnc_index(j, hicann) & 7u});
		rf.write<HicannPacketGen>({0, false, false});

		for (size_t i = 0; i < 10; ++i)
		{
			uint64_t sent = 0xfedcba98ull << (i % 32u);
			j.write<TxData>(sent, hicann);
			j.trigger<StartConfigPackage>(hicann);

			usleep(1000);

			uint64_t received = rf.read<HicannIfRxConfig>().data();
			CHECK(sent == received);
		}
	}
}

TEST_CASE("Highspeed write via Hicann Config, read via JTAG", "[.][hs]")
{
    auto node = GENERATE(hicann_nodes());
    CAPTURE(node);
    auto rf = EX.register_file(node);
    auto j = EX.jtag(node);
    auto fpga = EX.fpga(node);

    FOR_EACH_HICANN {
        highspeed_init(rf, j, fpga, hicann);
        CAPTURE(highspeed_status(rf, j, hicann));
        CAPTURE(hicann);

        // TODO
    }
}
