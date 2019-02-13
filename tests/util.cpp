#include "util.h"

std::vector<uint64_t> all_bits(size_t n)
{
	std::vector<uint64_t> bits;
	for (uint64_t i = 0; i < n; ++i)
	{
		bits.push_back(1 << i);
	}

	return bits;
}

std::vector<RMA2_Nodeid> NodesWithHicanns{};
std::vector<RMA2_Nodeid> NodesWithoutHicanns{};
RMA2_Nodeid HostNode{0};
RMA2_Nodeid NotExistingNode{0};
