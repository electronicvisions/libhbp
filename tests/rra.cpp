#include "helper/util.h"

using namespace extoll::library::rf;

TEST_CASE("Failing connections", "[.][rf][throw]")
{

	SECTION("Cannot connect to host")
	{
		REQUIRE_THROWS(EX.register_file(HostNode));
	}
}

TEST_CASE("Successful connections to Fpgas", "[rf][success]")
{
	SECTION("Fpga with Hicanns")
	{
		auto node = GENERATE(hicann_nodes());
		CAPTURE(node);
		REQUIRE_NOTHROW(EX.register_file(node));
	}
}

TEST_CASE("Read static registers", "[rf][static]")
{
	SECTION("Fpga with Hicann")
	{
		auto node = GENERATE(hicann_nodes());
		CAPTURE(node);

		auto r = EX.register_file(node);
		CHECK(r.read<Driver>().version() == 0xcafebabe);
		CHECK(r.read<Info>().node_id() == node);
	}
}


TEST_CASE("Write and read back", "[rf][rw]")
{
	SECTION("Fpga with Hicann")
	{
		auto node = GENERATE(hicann_nodes());
		CAPTURE(node);
		auto r = EX.register_file(node);

		r.write<JtagSend>({0xdeadbeef});
		CHECK(r.read<JtagSend>().data() == 0xdeadbeef);

		for (auto bit : all_bits())
		{
			r.write<JtagSend>({bit});

			CHECK(r.read<JtagSend>().data() == bit);
		}
	}
}
