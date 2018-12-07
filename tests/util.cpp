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
