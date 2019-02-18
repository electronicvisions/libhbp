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


template <typename T>
VectorGenerator<T>::VectorGenerator(const std::vector<T>& vec)
	: it(vec.cbegin()), end(vec.cend())
{}

template <typename T>
const T& VectorGenerator<T>::get() const
{
	return *it;
}

template <typename T>
bool VectorGenerator<T>::next()
{
	return ++it != end;
}

using namespace Catch::Generators;
using If = IGenerator<RMA2_Nodeid>;

Wrapper<RMA2_Nodeid> hicann_nodes()
{
	auto gen = new VectorGenerator<RMA2_Nodeid>(NodesWithHicanns);
	return {std::unique_ptr<If>(gen)};
}


Wrapper<RMA2_Nodeid> non_hicann_nodes()
{
	auto gen = new VectorGenerator<RMA2_Nodeid>(NodesWithoutHicanns);
	return {std::unique_ptr<If>(gen)};
}
