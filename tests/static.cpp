#include "util.h"


using namespace extoll::library::rf;

TEST_CASE("Basic static interface test", "[rf][static]")
{
	auto rf = Extoll::Instance().register_file(FPGA_HICANN);
	REQUIRE(rf.read<Driver>().version == 0xcafebabe);
}

TEST_CASE("Static interface is persistent", "[rf][static]")
{
	{
		auto rf = Extoll::Instance().register_file(FPGA_HICANN);
		rf.write<JtagSend>({0x1234567890abcdef});
	}

	{
		auto rf = Extoll::Instance().register_file(FPGA_HICANN);
		REQUIRE(rf.read<JtagSend>().raw == 0x1234567890abcdef);
	}
}
