#include <iostream>

enum class Flag
{
    A = 0x01,
    B = 0x02,
    C = 0x04,
    D = 0x08,
    E = 0x10
};

std::ostream& operator<<(std::ostream& out, Flag flag)
{
    return out << "Flag: " << std::hex << static_cast<int>(flag);
}

Flag operator|(Flag lhs, Flag rhs)
{
    return static_cast<Flag>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

bool operator&(Flag lhs, Flag rhs)
{
    return bool(static_cast<int>(lhs) & static_cast<int>(rhs));
}


int main()
{
    std::cout << Flag::A << "\n";

    Flag x = Flag::A | Flag::B;

    std::cout << x << "\n";

    std::cout << std::boolalpha << (Flag::A & Flag::B) << "\n";
    std::cout << std::boolalpha << (Flag::A & x) << "\n";
}