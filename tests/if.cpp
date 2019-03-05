#include "helper/util.h"


using namespace extoll::library::rf;

TEST_CASE("Basic static interface test", "[rf][static]")
{
	auto node = GENERATE(hicann_nodes());

	auto rf = Extoll::Instance().register_file(node);
	REQUIRE(rf.read<Driver>().version == 0xcafebabe);
}

TEST_CASE("Static interface is persistent", "[rf][static]")
{
	auto node = GENERATE(hicann_nodes());

	{
		auto rf = Extoll::Instance().register_file(node);
		rf.write<JtagSend>({0x1234567890abcdef});
	}

	{
		auto rf = Extoll::Instance().register_file(node);
		REQUIRE(rf.read<JtagSend>().raw == 0x1234567890abcdef);
	}
}


TEST_CASE("Basic oop interface test", "[rf][oop]")
{
	auto node = GENERATE(hicann_nodes());

	Extoll e;

	auto rf = e.register_file(node);
	REQUIRE(rf.read<Driver>().version == 0xcafebabe);
}

TEST_CASE("OOP interface is persistent", "[rf][oop]")
{
	auto node = GENERATE(hicann_nodes());

	Extoll e;

	{
		auto rf = e.register_file(node);
		rf.write<JtagSend>({0x1234567890abcdef});
	}

	{
		auto rf = e.register_file(node);
		REQUIRE(rf.read<JtagSend>().raw == 0x1234567890abcdef);
	}
}
