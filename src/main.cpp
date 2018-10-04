#include <iostream>

#include <hbp.h>

using std::cout;
using std::cerr;
using std::hex;

void print_readable_jtag(JTag& jtag)
{
    jtag.reset();
    //cout << "ID             : " << jtag.get(jtag::ID) << "\n";
    jtag.reset();
    cout << "Systime        : " << jtag.get(jtag::Systime) << "\n";
    jtag.reset();
    cout << "RxData         : " << jtag.get(jtag::RxData) << "\n";
    jtag.reset();
    cout << "Status         : " << jtag.get(jtag::Status) << "\n";
    cout << "CrcCount       : " << jtag.get(jtag::CrcCount) << "\n";
    cout << "ArqTxPckNum    : " << jtag.get(jtag::ArqTxPckNum) << "\n";
    cout << "ArqRxPckNum    : " << jtag.get(jtag::ArqRxPckNum) << "\n";
    cout << "ArqRxDropNum   : " << jtag.get(jtag::ArqRxDropNum) << "\n";
    cout << "ArqTxTimeoutNum: " << jtag.get(jtag::ArqTxTimeoutNum) << "\n";
    cout << "ArqRxTimeoutNum: " << jtag.get(jtag::ArqRxTimeoutNum) << "\n";
}

int _main(RMA2_Nodeid node, uint8_t hicann)
{
    HBP hbp;
    hbp.configure_partner_host_for(node);
    auto rf = hbp.rra(node);
    auto jtag = hbp.jtag(node);

    rf.set(rf::HicannChannel, hicann);
    cout << "Driver:      " << hex << rf.get(rf::Driver) << "\n";
    cout << "Id:          " << hex << rf.get(rf::Info) << "\n";
    cout << "Channel:     " << hex << rf.get(rf::HicannChannel) << "\n\n";

    print_readable_jtag(jtag);

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