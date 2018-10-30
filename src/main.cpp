#include <iostream>
#include <bitset>

#include <hbp.h>
#include <tests/test.h>
#include <tests/switchram.h>
#include <tests/jtagrw.h>

using std::cout;
using std::cerr;
using std::hex;

using namespace rf;
using namespace jtag;


void print_systime_diff(JTag& jtag)
{
    auto start = jtag.read<Systime>();
    auto end = jtag.read<Systime>();

    std::cout << std::dec;
    std::cout << "SYSTIME    : " << end << " - " << start << " = "
        << ((end - start) & 0x7fff) << "\n";
}

int _main(RMA2_Nodeid node, uint8_t hicann_number)
{
    Runner runner;
    runner.add<SwitchRam>(node, hicann_number);
    runner.add<JtagRw>(node, hicann_number);
    runner.run();

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        cerr << "usage: " << argv[0] << " NODE HICANN\n";
        return EXIT_FAILURE;
    }

    auto node = RMA2_Nodeid(std::stoi(argv[1], nullptr, 0));
    auto hicann = uint8_t(std::stoi(argv[2], nullptr, 0));

    if (hicann > 7)
    {
        cerr << "HICANN must be in range [0, 7]\n";
        return EXIT_FAILURE;
    }

    try
    {
        return _main(node, hicann);
    }
    catch (std::exception& e)
    {
        cerr << "ERROR: " << e.what() << "\n";
    }
}
