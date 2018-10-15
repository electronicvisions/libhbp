#include <iostream>
#include <bitset>

#include <hbp.h>
#include <tests/test.h>
#include <tests/switchram.h>

using std::cout;
using std::cerr;
using std::hex;

using namespace rf;


int _main(RMA2_Nodeid node, uint8_t)
{
    HBP hbp;
    auto fpga = hbp.fpga(node);
    auto rf = hbp.register_file(node);
    auto jtag = hbp.jtag(node);

    fpga.reset();
    jtag.reset();


    cout << "DRIVER   0x: " << std::hex << rf.read<Driver>().version << "\n";
    cout << "ID       0x: " << std::hex << jtag.read(jtag::ID) << "\n";
    cout << "SYSTIME  0x: " << std::dec << jtag.read(jtag::Systime) << "\n";
    cout << "SYSTIME  0x: " << std::dec << jtag.read(jtag::Systime) << "\n";
    cout << "STATUS   0x: " << std::hex << jtag.read(jtag::Status) << "\n";
    cout << "CRCCOUNT 0x: " << std::hex << jtag.read(jtag::CrcCount) << "\n";
    jtag.trigger(jtag::ResetCrcCount);
    cout << "CRCCOUNT 0x: " << std::hex << jtag.read(jtag::CrcCount) << "\n";

    auto ibias = jtag.read_write(jtag::IBias, std::bitset<15>("101101010111").to_ullong());
    cout << "IBIAS    : " << std::bitset<15>(ibias) << "\n";
    ibias = jtag.read_write(jtag::IBias, std::bitset<15>("101101010111").to_ullong());
    cout << "IBIAS    : " << std::bitset<15>(ibias) << "\n";

    std::bitset<32> in("101010101111");

    cout << "BEFORE BYPASS\n";
    cout << "IN : " << in << "\n";
    cout << "OUT: " << jtag.shift_through(in) << "\n\n";

    jtag.set_bypass();
    cout << "AFTER BYPASS\n";


    for (uint16_t i = 0; i < 14; ++i)
    {
        cout << "SHIFT: " << std::dec << i << "\n";
        cout << "IN : " << in << "\n";
        cout << "OUT: " << jtag.shift_through(in, i) << "\n\n";
    }

    Runner runner;
    runner.add<SwitchRam>(2);

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
        cerr << typeid(e).name() << "\n";
        cerr << "ERROR: " << e.what() << "\n";
    }
}