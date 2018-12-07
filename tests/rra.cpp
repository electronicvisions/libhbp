#include "util.h"


using namespace extoll::library::rf;

TEST_CASE("Failing connections", "[rf]")
{
	Extoll e;

	SECTION("Cannot connect to host")
	{
		REQUIRE_THROWS(e.register_file(HOST));
	}

	SECTION("Cannot connect to non-existing node")
	{
		REQUIRE_THROWS(e.register_file(UNKNOWN));
	}
}

TEST_CASE("Successful connections to FPGAs", "[rf]")
{
	Extoll e;

	SECTION("FPGA without HICANNs")
	{
		REQUIRE_NOTHROW(e.register_file(FPGA));
	}

	SECTION("FPGA with HICANNs")
	{
		REQUIRE_NOTHROW(e.register_file(FPGA_HICANN));
	}
}

TEST_CASE("Read static registers", "[rf]")
{
	Extoll e;

	SECTION("FPGA without HICANN")
	{
		auto r = e.register_file(FPGA);

		CHECK(r.read<Driver>().version == 0xcafebabe);

		auto info = r.read<Info>();
		CHECK(info.node_id == FPGA);
	}

	SECTION("FPGA with HICANN")
	{
		auto r = e.register_file(FPGA_HICANN);

		CHECK(r.read<Driver>().version == 0xcafebabe);

		auto info = r.read<Info>();
		CHECK(info.node_id == FPGA_HICANN);
	}
}


TEST_CASE("Write and read back", "[rf]")
{
	Extoll e;

	SECTION("FPGA without HICANN")
	{
		auto r = e.register_file(FPGA);

		r.write<JtagSend>({0xdeadbeef});
		CHECK(r.read<JtagSend>().raw == 0xdeadbeef);

		for (auto bit : all_bits())
		{
			r.write<JtagSend>({bit});

			CHECK(r.read<JtagSend>().raw == bit);
		}
	}

	SECTION("FPGA with HICANN")
	{
		auto r = e.register_file(FPGA_HICANN);

		r.write<JtagSend>({0xdeadbeef});
		CHECK(r.read<JtagSend>().raw == 0xdeadbeef);

		for (auto bit : all_bits())
		{
			r.write<JtagSend>({bit});

			CHECK(r.read<JtagSend>().raw == bit);
		}
	}
}
