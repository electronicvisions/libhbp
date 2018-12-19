#include <iostream>
#include <cstring>
#include <bitset>
#include <cinttypes>
#include <type_traits>


template <size_t WIDTH>
union Pack {
    uint64_t full;
    uint64_t half : WIDTH;
};

int main()
{
    Pack<3> p;
    p.full = 0xabcdabcdabcdabcd;
    p.half = 1;

    std::cout << std::hex << p.full << "\n";

}
