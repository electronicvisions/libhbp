#include "util.h"

using namespace extoll::library::jtag;

#define FOR_EACH_HICANN for (uint8_t hicann = 0; hicann < j.active_hicanns(); ++hicann)

#define EX Extoll::Instance()
#define CREATE() auto j = Extoll::Instance().jtag(FPGA_HICANN);\
	j.reset();



TEST_CASE("FPGA without HICANN cannot open JTAG connection", "[jtag][throw]")
{
	REQUIRE_THROWS_WITH(EX.jtag(FPGA), Contains("no HICANN"));
}

TEST_CASE("FPGA with HICANN counts HICANNs", "[jtag]")
{
	CREATE()

	REQUIRE(j.active_hicanns() > 0);
}


TEST_CASE("FPGA can query static READID", "[jtag]")
{
	CREATE()

	FOR_EACH_HICANN {
		CHECK(j.read<ID>(hicann) == 0x14849434);
		CHECK(j.read<ID>(hicann) == 0x14849434);
	}
}


TEST_CASE("FPGA can query changing register", "[jtag][ok]")
{
	CREATE()

	FOR_EACH_HICANN {
		CHECK(j.read<Systime>(hicann) != j.read<Systime>(hicann));
	}
}


TEST_CASE("FPGA can read back sent JTAG data", "[jtag]")
{
	CREATE()

	SECTION("writing a certain value")
	{
		FOR_EACH_HICANN {
			j.write<IBias>(0x7fff, hicann);
			CHECK(j.write<IBias>(0x0, hicann) == 0x7fff);
		}
	}

	SECTION("writing all bits")
	{
		FOR_EACH_HICANN {
			for (auto bit : all_bits(15))
			{
				CHECK(j.write<IBias>(bit, hicann) == 0x0);
				CHECK(j.write<IBias>(0x0, hicann) == bit);
			}
		}
	}
}

TEST_CASE("FPGA can mix read/write to different HICANNs", "[jtag]")
{
	CREATE()

	CHECKED_IF(j.active_hicanns() > 1)
	{
		FOR_EACH_HICANN
		{
			j.write<IBias>(0xc4 + hicann, hicann);
		}

		FOR_EACH_HICANN
		{
			CHECK(j.write<IBias>(0, hicann) == 0xc4 + hicann);
		}
	}
}
