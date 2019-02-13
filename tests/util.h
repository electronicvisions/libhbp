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

#endif
