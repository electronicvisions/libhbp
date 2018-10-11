#include <iostream>
#include <cstring>
#include <bitset>

struct JtagCmd
{


    uint64_t type : 3;
    uint64_t length : 10;
    bool pause : 1;
    bool execute : 1;


    const static bool X = true;
    const static int YOLO = 3;
};

struct Reset
{
    const static int YOLO = 2;
    const static bool X = true;
    bool a : 1;
    bool b : 1;
    bool c : 1;
};

template <typename T>
uint64_t rf_to_data(const T& rf)
{
    uint64_t data = 0;
    memcpy(&data, &rf, sizeof(T));
    return data;
}

template <typename RF>
void send(RF&& rf)
{
    uint64_t data = rf_to_data(std::forward<RF>(rf));

    std::cout << "SEND: " << std::bitset<16>(data) << "\n";
}

static_assert(sizeof(JtagCmd) == 8, "Bit Field size incorrect!");
static_assert(sizeof(Reset) == 1, "Bit Field size incorrect!");

using namespace std;

int main()
{
    JtagCmd cmd{3, 10, true, true};

    cout << bitset<16>(rf_to_data(cmd)) << "\n";

    send(JtagCmd{5, 42, true, false});
    send<JtagCmd>({7, 10, false, true});

    send<Reset>({true, false, true});
}