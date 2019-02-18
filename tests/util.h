#ifndef __EXTOLL_TEST_RUNNER_HELPER__
#define __EXTOLL_TEST_RUNNER_HELPER__

#include <catch.hpp>

#include <extoll/extoll.h>
#include <vector>

using Extoll = extoll::library::Extoll;
using namespace Catch::Matchers;

std::vector<uint64_t> all_bits(size_t n=64);

extern std::vector<RMA2_Nodeid> NodesWithHicanns;
extern std::vector<RMA2_Nodeid> NodesWithoutHicanns;
extern RMA2_Nodeid HostNode;
extern RMA2_Nodeid NotExistingNode;

template <typename T>
class VectorGenerator : public Catch::Generators::IGenerator<T>
{
	using It = typename std::vector<T>::const_iterator;
	It it;
	It end;

public:
	explicit VectorGenerator(const std::vector<T>& vec);
	const T& get() const override;
	bool next() override;
};

template <typename T>
using Wrapper = Catch::Generators::GeneratorWrapper<T>;

Wrapper<RMA2_Nodeid> hicann_nodes();
Wrapper<RMA2_Nodeid> non_hicann_nodes();

#endif
