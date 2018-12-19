#ifndef __EXTOLL_TEST_RUNNER_HELPER__
#define __EXTOLL_TEST_RUNNER_HELPER__

#include <catch.hpp>

#include <extoll/extoll.h>
#include <vector>

using Extoll = extoll::library::Extoll;
using namespace Catch::Matchers;

const RMA2_Nodeid HOST = 1;
const RMA2_Nodeid FPGA = 131;
const RMA2_Nodeid FPGA_HICANN = 130;
const RMA2_Nodeid UNKNOWN = 100;

std::vector<uint64_t> all_bits(size_t n=64);

#endif
