#include <iostream>
#include <bitset>

#include <extoll/extoll.h>

using std::cout;
using std::cerr;
using std::hex;

using namespace extoll::library;
using namespace rf;
using namespace jtag;



#include <cassert>

int _main(RMA2_Nodeid node, uint8_t hicann)
{
    auto rf = Extoll::Instance().register_file(node);
    auto jtag = Extoll::Instance().jtag(node);

    std::cout << jtag.read<ID>(hicann) << "\n";
    int i;
    rf.write<JtagSend>({0});
    std::cin >> i;
    rf.write<JtagCmd>({0, 6, false, true});
    std::cin >> i;
    rf.write<JtagCmd>({JtagCmd::DR, 32, false, true});
    std::cin >> i;
    std::cout << std::hex << rf.read<JtagReceive>().raw << "\n";

    

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
