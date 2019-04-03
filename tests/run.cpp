#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "helper/util.h"

using namespace Catch::clara;

#include <iostream>
int main(int argc, char** argv)
{
	Catch::Session session;

    auto& nodes_with_hicanns = get_nodes_with_hicanns();
    auto& nodes_without_hicanns = get_nodes_without_hicanns();

	auto cli = session.cli()
		| Opt(nodes_with_hicanns, "hicann nodes")
			["-y"]["--hicann-nodes"]
			("Node Id of nodes with Hicanns")
		| Opt(nodes_without_hicanns, "non-hicann nodes")
			["-j"]["--non-hicann-nodes"]
		| Opt(HostNode, "host node")
			["-k"]["--host-node"]
		| Opt(NotExistingNode, "not existing node")
			["--not-existing-node"];

	session.cli(cli);

	auto ret = session.applyCommandLine(argc, argv);

	if (HostNode == 0)
	{
		std::cerr << "Host node must be provided\n";
		return EXIT_FAILURE;
	}

	if (NotExistingNode == 0)
	{
		std::cout << "Skipping not-existing-node test\n";
	}
	else
	{
		std::cout << "Not-existing-node: " << NotExistingNode << "\n";
	}

	if (nodes_with_hicanns.empty())
	{
		std::cout << "No nodes with hicanns provided\n";
	}
	else
	{
		std::cout << "Nodes with hicanns: ";
		for (auto n : nodes_with_hicanns)
		{
			std::cout << n << " ";
		}
		std::cout << "\n";
	}
	if (nodes_without_hicanns.empty())
	{
		std::cout << "No nodes without hicanns provided\n";
	}
	else
	{
		std::cout << "Nodes without hicanns: ";
		for (auto n : nodes_without_hicanns)
		{
			std::cout << n << " ";
		}
		std::cout << "\n";
	}

	if (ret)
	{
		return ret;
	}

	return session.run();
}
