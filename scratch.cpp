#include <iostream>
#include <cstring>
#include <bitset>
#include <cinttypes>
#include <type_traits>


using namespace std;

using RMA2_NLA = int;

struct JtagCmd {
    union {
        struct {
            uint64_t type: 3;
            uint64_t length: 10;
            bool pause: 1;
            bool execute: 1;
        };
        uint64_t raw;
    };

    enum Type {
        Reset = 0,
        IR = 1,
        DR = 2,
        EnableClock = 4,
        DisableClock = 5,
    };
    const static RMA2_NLA ADDRESS = 0x400;
    const static bool READABLE = true;
    const static bool WRITABLE = true;
};

static_assert(sizeof(JtagCmd) == sizeof(uint64_t), "FAIL");
static_assert(std::is_trivial<JtagCmd>::value, "FAIL");

template <typename RF>
void write(RF&& rf)
{
    static_assert(RF::ADDRESS >= 0, "register file address must be positive!");
    static_assert(RF::ADDRESS <= 0x180d0, "register file address too large!");
    static_assert(RF::WRITABLE, "register file must be writable!");

    std::cout << std::bitset<64>(rf.raw) << "\n";
    std::cout << rf.type << "\n";
    std::cout << rf.length << "\n";
    std::cout << rf.pause << "\n";
    std::cout << rf.execute << "\n";
}

int main()
{

    // JtagCmd j{1, 10, true, false};
    JtagCmd j;
    j.raw = 100;

    std::cout << std::bitset<64>(j.raw) << "\n";
    std::cout << j.type << ", " << j.length << ", " << j.pause << ", " << j.execute << "\n";
}
