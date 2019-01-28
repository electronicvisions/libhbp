#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "util.h"

using namespace Catch::clara;

#include <iostream>
int main(int argc, char** argv)
{
	Catch::Session session;


	auto cli = session.cli()
		| Opt(NodesWithHicanns, "hicann nodes")
			["-y"]["--hicann-nodes"]
			("Node Id of nodes with Hicanns")
		| Opt(NodesWithoutHicanns, "non-hicann nodes")
			["-j"]["--non-hicann-nodes"]
		| Opt(HostNode, "host node")
			["-k"]["--host-node"];

	session.cli(cli);

	auto ret = session.applyCommandLine(argc, argv);

	if (HostNode == 0)
	{
		std::cerr << "Host node must be provided\n";
		return EXIT_FAILURE;
	}

	if (NodesWithHicanns.size() == 0)
	{
		std::cout << "No nodes with hicanns provided\n";
	}
	else
	{
		std::cout << "Nodes with hicanns: ";
		for (auto n : NodesWithHicanns)
		{
			std::cout << n << " ";
		}
		std::cout << "\n";
	}
	if (NodesWithoutHicanns.size() == 0)
	{
		std::cout << "No nodes without hicanns provided\n";
	}
	else
	{
		std::cout << "Nodes without hicanns: ";
		for (auto n : NodesWithoutHicanns)
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
