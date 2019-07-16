#include "helper/util.h"

using namespace extoll::library::jtag;


TEST_CASE("Fpga with Hicann counts Hicanns", "[jtag]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);

	auto j = EX.jtag(node);

	REQUIRE(j.active_hicanns() > 0);
}


TEST_CASE("Fpga can query static READID", "[jtag]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);

	auto j = EX.jtag(node);

	FOR_EACH_HICANN {
		CHECK(j.read<ID>(hicann) == 0x14849434);
		CHECK(j.read<ID>(hicann) == 0x14849434);
	}
}


TEST_CASE("Fpga can query changing register", "[jtag][ok]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);

	auto j = EX.jtag(node);

	FOR_EACH_HICANN {
		CHECK(j.read<Systime>(hicann) != j.read<Systime>(hicann));
	}
}


TEST_CASE("Fpga can read back sent JTAG data", "[jtag]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);

	auto j = EX.jtag(node);

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

TEST_CASE("Fpga can mix read/write to different Hicanns", "[jtag]")
{
	auto node = GENERATE(hicann_nodes());
	CAPTURE(node);

	auto j = EX.jtag(node);

	CHECKED_IF(j.active_hicanns() > 1)
	{
		FOR_EACH_HICANN
		{
			j.write<IBias>(0xc4ull + hicann, hicann);
		}

		FOR_EACH_HICANN
		{
			CHECK(j.write<IBias>(0, hicann) == 0xc4 + hicann);
		}
	}
}
