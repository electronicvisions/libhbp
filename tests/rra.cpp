#include "util.h"

#define EX Extoll::Instance()
#define CREATE(NODE) auto r = Extoll::Instance().register_file(NODE);\

using namespace extoll::library::rf;

TEST_CASE("Failing connections", "[rf][throw]")
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

TEST_CASE("Successful connections to FPGAs", "[rf][success]")
{
	SECTION("FPGA without HICANNs")
	{
		for (auto node : NodesWithoutHicanns)
		{
			DYNAMIC_SECTION("node is " << node)
			{
				REQUIRE_NOTHROW(EX.register_file(node));
			}
		}

	}

	SECTION("FPGA with HICANNs")
	{
		for (auto node : NodesWithHicanns)
		{
			DYNAMIC_SECTION("node is " << node)
			{
				REQUIRE_NOTHROW(EX.register_file(node));
			}
		}
	}
}

TEST_CASE("Read static registers", "[rf][static]")
{
	SECTION("FPGA without HICANN")
	{
		for (auto node : NodesWithoutHicanns)
		{
			DYNAMIC_SECTION("node is " << node)
			{
				auto r = EX.register_file(node);

				CHECK(r.read<Driver>().version == 0xcafebabe);

				auto info = r.read<Info>();
				CHECK(info.node_id == node);
			}
		}

	}

	SECTION("FPGA with HICANN")
	{
		for (auto node : NodesWithHicanns)
		{
			DYNAMIC_SECTION("node is " << node)
			{
				auto r = EX.register_file(node);

				CHECK(r.read<Driver>().version == 0xcafebabe);

				auto info = r.read<Info>();
				CHECK(info.node_id == node);
			}
		}
	}
}


TEST_CASE("Write and read back", "[rf][rw]")
{
	SECTION("FPGA without HICANN")
	{
		for (auto node : NodesWithoutHicanns)
		{
			DYNAMIC_SECTION("node is" << node)
			{
				auto r = EX.register_file(node);

				r.write<JtagSend>({0xdeadbeef});
				CHECK(r.read<JtagSend>().raw == 0xdeadbeef);

				for (auto bit : all_bits())
				{
					r.write<JtagSend>({bit});

					CHECK(r.read<JtagSend>().raw == bit);
				}
			}
		}
	}

	SECTION("FPGA with HICANN")
	{
		for (auto node : NodesWithHicanns)
		{
			DYNAMIC_SECTION("node is" << node)
			{
				auto r = EX.register_file(node);

				r.write<JtagSend>({0xdeadbeef});
				CHECK(r.read<JtagSend>().raw == 0xdeadbeef);

				for (auto bit : all_bits())
				{
					r.write<JtagSend>({bit});

					CHECK(r.read<JtagSend>().raw == bit);
				}
			}
		}
	}
}
