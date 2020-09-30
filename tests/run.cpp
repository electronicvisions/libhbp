#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

#include <regex>
#include <vector>

#include "helper/util.h"

using namespace Catch::clara;

void read_node_ids_from_emp_ctrl(Nodes& nodes)
{
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("emp-ctrl network listnodes", "r"), pclose);

	if (!pipe) {
		std::cout << "Could not automatically determine nodes\n";
		std::exit(1);
	}

	while (fgets(buffer.data(), int(buffer.size()), pipe.get()) != nullptr) {
		result += buffer.data();
	}

	std::size_t pos = result.find_first_of('[');

	while (pos != std::string::npos) {
		auto sep = result.find_first_of('|', pos);
		if (sep == std::string::npos) {
			return;
		}
		auto node_id = RMA2_Nodeid(std::stoi(result.substr(pos + 1, sep - pos - 1)));
		nodes.push_back(node_id);

		pos = result.find_first_of('[', sep);
	}
}

void read_node_ids_from_arg(Nodes& nodes, const std::string& arg)
{
	std::istringstream node_stream(arg);
	std::string node;

	while (std::getline(node_stream, node, ',')) {
		nodes.push_back(RMA2_Nodeid(std::stoi(node)));
	}
}

#include <iostream>
int main(int argc, char** argv)
{
	Catch::Session session;

	auto& nodes = get_nodes_with_hicanns();
	std::string nodes_arg;

	auto cli =
	    session.cli() | Opt(nodes_arg, "hicann nodes")["-N"]["--node"](
	                        "Node Id of nodes with Hicanns or comma separated list of node Ids");

	session.cli(cli);

	auto ret = session.applyCommandLine(argc, argv);

	RMA2_Port port;
	rma2_open(&port);
	HostNode = rma2_get_nodeid(port);
	rma2_close(port);

	if (nodes_arg.empty()) {
		read_node_ids_from_emp_ctrl(nodes);
	} else {
		read_node_ids_from_arg(nodes, nodes_arg);
	}

	nodes.erase(std::remove(nodes.begin(), nodes.end(), HostNode), nodes.end());

	std::cout << "Host " << HostNode << "\n";
	for (auto node : nodes) {
		std::cout << "Node " << node << "\n";
	}

	if (ret) {
		return ret;
	}

	return session.run();
}
