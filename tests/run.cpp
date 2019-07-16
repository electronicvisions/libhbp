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
		| Opt(NotExistingNode, "not existing node")
			["--not-existing-node"];

	session.cli(cli);

	auto ret = session.applyCommandLine(argc, argv);

	RMA2_Port port;
	rma2_open(&port);
	HostNode = rma2_get_nodeid(port);
	rma2_close(port);

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
