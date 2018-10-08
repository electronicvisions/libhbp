#include <iostream>

#include <hbp.h>

using std::cout;
using std::cerr;
using std::hex;

void print_readable_jtag(JTag& jtag)
{
    jtag.reset();
    //cout << "ID             : " << jtag.read(jtag::ID) << "\n";
    jtag.reset();
    cout << "Systime        : " << jtag.read(jtag::Systime) << "\n";
    jtag.reset();
    cout << "RxData         : " << jtag.read(jtag::RxData) << "\n";
    jtag.reset();
    cout << "Status         : " << jtag.read(jtag::Status) << "\n";
    cout << "CrcCount       : " << jtag.read(jtag::CrcCount) << "\n";
    cout << "ArqTxPckNum    : " << jtag.read(jtag::ArqTxPckNum) << "\n";
    cout << "ArqRxPckNum    : " << jtag.read(jtag::ArqRxPckNum) << "\n";
    cout << "ArqRxDropNum   : " << jtag.read(jtag::ArqRxDropNum) << "\n";
    cout << "ArqTxTimeoutNum: " << jtag.read(jtag::ArqTxTimeoutNum) << "\n";
    cout << "ArqRxTimeoutNum: " << jtag.read(jtag::ArqRxTimeoutNum) << "\n";
}

int _main(RMA2_Nodeid node, uint8_t hicann)
{
    HBP hbp;
    auto fpga = hbp.fpga(node);
    auto rf = hbp.register_file(node);
    auto jtag = hbp.jtag(node);

    fpga.reset();
    fpga.configure_partner_host();

    auto id = rf.read<Info>();

    rf.write<HicannChannel>(hicann);
    cout << "Driver:      " << hex << rf.read<Driver>() << "\n";
    cout << "Id:          " << hex << id.node_id << ", " << id.guid << "\n";
    cout << "Channel:     " << hex << int(rf.read<HicannChannel>()) << "\n\n";

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