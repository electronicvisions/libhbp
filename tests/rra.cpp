#include "helper/util.h"

using namespace extoll::library::rf;

TEST_CASE("Failing connections", "[.][rf][throw]")
{

	SECTION("Cannot connect to host")
	{
		REQUIRE_THROWS(EX.register_file(HostNode));
	}

	if (NotExistingNode)
	{
		SECTION("Cannot connect to non-existing node")
		{
			REQUIRE_THROWS(EX.register_file(NotExistingNode));
		}
	}
}

TEST_CASE("Successful connections to Fpgas", "[rf][success]")
{
	SECTION("Fpga without Hicanns")
	{
		auto node = GENERATE(non_hicann_nodes());
		CAPTURE(node);
		REQUIRE_NOTHROW(EX.register_file(node));
	}

	SECTION("Fpga with Hicanns")
	{
		auto node = GENERATE(hicann_nodes());
		CAPTURE(node);
		REQUIRE_NOTHROW(EX.register_file(node));
	}
}

TEST_CASE("Read static registers", "[rf][static]")
{
	SECTION("Fpga without Hicann")
	{
		auto node = GENERATE(non_hicann_nodes());
		CAPTURE(node);

		auto r = EX.register_file(node);
		CHECK(r.read<Driver>().version() == 0xcafebabe);
		CHECK(r.read<Info>().node_id() == node);
	}

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
	SECTION("Fpga without Hicann")
	{
		auto node = GENERATE(non_hicann_nodes());
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
