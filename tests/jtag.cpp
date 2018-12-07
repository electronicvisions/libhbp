#include "util.h"

using namespace extoll::library::jtag;

TEST_CASE("FPGA without HICANN cannot open JTAG connection", "[jtag]")
{
	Extoll e;

	REQUIRE_THROWS_WITH(e.jtag(FPGA), Contains("no HICANN"));
}


TEST_CASE("FPGA can query static READID", "[jtag]")
{
	Extoll e;
	auto j = e.jtag(FPGA_HICANN);

	CHECK(j.read<ID>() == 0x14849434);
	CHECK(j.read<ID>() == 0x14849434);
}


TEST_CASE("FPGA can query changing register", "[jtag]")
{
	Extoll e;
	auto j = e.jtag(FPGA_HICANN);

	REQUIRE(j.read<Systime>() != j.read<Systime>());
}


TEST_CASE("FPGA can read back sent JTAG data", "[jtag]")
{
	Extoll e;
	auto j = e.jtag(FPGA_HICANN);

	SECTION("writing a certain value")
	{
		j.write<IBias>(0x7fff);
		CHECK(j.write<IBias>(0x0) == 0x7fff);
	}

	SECTION("writing all bits")
	{
		for (auto bit : all_bits(15))
		{
			CHECK(j.write<IBias>(bit) == 0x0);
			CHECK(j.write<IBias>(0x0) == bit);
		}
	}

}


TEST_CASE("JTAG BYPASS offset", "[jtag][bypass]")
{
	Extoll e;
	auto j = e.jtag(FPGA_HICANN);

	j.set_bypass();

	SECTION("shift width = data length + 1")
	{
		j.set_data(0, 64);
		CHECK(j.set_get_data(0xaa, 9) == 0x154);
		j.set_data(0, 64);
		CHECK(j.set_get_data(0x555, 13) == 0xaaa);
	}

	SECTION("shift width = data length")
	{
		j.set_data(0, 64);
		CHECK(j.set_get_data(0xaa, 8) == 0x54);
		j.set_data(0, 64);
		CHECK(j.set_get_data(0x555, 11) == 0x2aa);
	}

}
