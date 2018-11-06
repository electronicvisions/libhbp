#include <iostream>
#include <bitset>

#include <extoll/extoll.h>
#include <tests/test.h>
#include <tests/switchram.h>
#include <tests/jtagrw.h>
#include <tests/register_file.h>

using std::cout;
using std::cerr;
using std::hex;

using namespace extoll::library;
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

#include <cassert>

#define ASSERT(RC) assert((RC) == RMA2_SUCCESS);

int _main(RMA2_Nodeid node, uint8_t hicann_number)
{
    Runner runner;
    // runner.add<SwitchRam>(node, hicann_number);
    runner.add<RegisterFileTest>(node);
    runner.add<JtagRw>(node, hicann_number);
    runner.run();

    /*
    RMA2_Port port;
    ASSERT( rma2_open(&port) )
    RMA2_VPID vpid = rma2_get_vpid(port);
    RMA2_Handle handle;
    auto options = static_cast<RMA2_Connection_Options>(RMA2_CONN_DEFAULT | RMA2_CONN_RRA);
    ASSERT( rma2_connect(port, node, vpid, options, &handle) )

    char buffer[1024];
    for (char& i : buffer)
    {
        i = 0;
    }
    RMA2_Region* region;
    ASSERT( rma2_register(port, buffer, 1024, &region) )

    ASSERT (rma2_post_get_qw(port, handle, region, 0, 8, 0x8008, RMA2_COMPLETER_NOTIFICATION, RMA2_CMD_DEFAULT) )
    RMA2_Notification* notification;
    std::cout << "waiting for notification\n";
    ASSERT( rma2_noti_get_block(port, &notification) )
    rma2_noti_dump(notification);
    rma2_noti_free(port, notification);

    auto qw = reinterpret_cast<uint64_t*>(buffer);
    std::cout << std::hex << *qw << "\n";

    ASSERT( rma2_disconnect(port, handle) )
    ASSERT( rma2_close(port) )
    */
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
