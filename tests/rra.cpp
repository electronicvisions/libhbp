#include "util.h"

#define EX Extoll::Instance()
#define CREATE(NODE) auto r = Extoll::Instance().register_file(NODE);\

using namespace extoll::library::rf;

TEST_CASE("Failing connections", "[rf][throw]")
{

	SECTION("Cannot connect to host")
	{
		REQUIRE_THROWS(EX.register_file(HOST));
	}

	SECTION("Cannot connect to non-existing node")
	{
		REQUIRE_THROWS(EX.register_file(UNKNOWN));
	}
}

TEST_CASE("Successful connections to FPGAs", "[rf][success]")
{
	SECTION("FPGA without HICANNs")
	{
		REQUIRE_NOTHROW(EX.register_file(FPGA));
	}

	SECTION("FPGA with HICANNs")
	{
		REQUIRE_NOTHROW(EX.register_file(FPGA_HICANN));
	}
}

TEST_CASE("Read static registers", "[rf][static]")
{
	SECTION("FPGA without HICANN")
	{
		auto r = EX.register_file(FPGA);

		CHECK(r.read<Driver>().version == 0xcafebabe);

		auto info = r.read<Info>();
		CHECK(info.node_id == FPGA);
	}

	SECTION("FPGA with HICANN")
	{
		auto r = EX.register_file(FPGA_HICANN);

		CHECK(r.read<Driver>().version == 0xcafebabe);

		auto info = r.read<Info>();
		CHECK(info.node_id == FPGA_HICANN);
	}
}


TEST_CASE("Write and read back", "[rf][rw]")
{
	SECTION("FPGA without HICANN")
	{
		auto r = EX.register_file(FPGA);

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
		auto r = EX.register_file(FPGA_HICANN);

		r.write<JtagSend>({0xdeadbeef});
		CHECK(r.read<JtagSend>().raw == 0xdeadbeef);

		for (auto bit : all_bits())
		{
			r.write<JtagSend>({bit});

			CHECK(r.read<JtagSend>().raw == bit);
		}
	}
}
