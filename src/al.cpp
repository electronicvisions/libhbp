#include <iostream>
#include <bitset>
#include <vector>

#include <extoll/extoll.h>

using std::cout;
using std::cerr;
using std::hex;
using std::dec;
using namespace extoll::library;
using namespace extoll::library::rf;

struct TestMode
{
    RegisterFile& rf;

    explicit TestMode(RegisterFile& rf_) : rf(rf_)
    {
        rf.write<TestControlEnable>({true});
        cout << "INFO: test mode is enabled: " << std::boolalpha << enabled() << "\n";
    }

    bool enabled()
    {
        return rf.read<TestControlEnable>().enable();
    }

    ~TestMode()
    {
        cout << "INFO: waiting...\n";
        wait();
        rf.write<TestControlEnable>({false});
        cout << "INFO: test mode is disabled: " << std::boolalpha << !enabled() << "\n";
    }

    void wait()
    {
        while(rf.read<TestControlStart>().start())
        {
            usleep(1000);
        }
    }
};

void run_test(RMA2_Nodeid node, uint64_t value, bool increment, int64_t count, int64_t delay)
{
    auto rf = Extoll::Instance().register_file(node);
    auto fpga = Extoll::Instance().fpga(node);
    auto& buffer = Extoll::Instance().hicann_config(node);

    cout << "INFO: current version: " << rf.read<Version>().number() << "\n";

    if (rf.read<TestControlEnable>().enable())
    {
        cout << "WARNING: test mode was already enabled\n";
    }

    fpga.configure_partner_host();
    std::cout << "INFO: host endpoint: 0x" << hex << rf.read<HostEndpoint>().raw << "\n";
    auto start_address = rf.read<HicannBufferCurrentAddress>().data();
    std::cout << "INFO: current address: 0x" << hex << start_address << "\n";

    std::vector<uint64_t> result;
    {
        TestMode tm{rf};

        rf.write<TestControlType>({TestControlType::HicannConfig});
        rf.write<TestControlData>({value});
        rf.write<TestControlConfig>({uint32_t(count), uint32_t(delay), increment});
        rf.write<TestControlStart>({true});

        try
        {
            while (true)
            {
                auto v = buffer.get();
                result.push_back(v);
                buffer.notify();
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "EXCEPTION: " << e.what() << "\n";
        }
    }

    auto end_address = rf.read<HicannBufferCurrentAddress>().data();
    cout << "INFO: current address: 0x" << hex << end_address << "\n";
    cout << "INFO: difference: " << dec << end_address - start_address << "\n";
    cout << "INFO: result length: " << dec << result.size() << "\n";
    cout << "[";
    for (auto& v : result)
    {
        cout << dec << v << " ";
    }
    cout << "\b]\n";
}   

int print_usage(const char* program)
{
    cerr << "ERROR: usage: " << program << " NODE:int VALUE:uint INCREMENT:bool COUNT:int DELAY:int\n";
    return EXIT_FAILURE;
}

int main(int argc, char** argv)
{
    if (argc != 6)
    {
        return print_usage(argv[0]);
    }

    auto node = RMA2_Nodeid(std::stoi(argv[1], nullptr, 0));
    auto value = std::stoull(argv[2], nullptr, 0);
    bool increment;

    if (!strcmp(argv[3], "true"))
    {
        increment = true;
    }
    else if (!strcmp(argv[3], "false"))
    {
        increment = false;
    }
    else
    {
        cerr << argv[3] << " is not a valid bool\n";
        return print_usage(argv[0]);
    }

    auto count = std::stoll(argv[4], nullptr, 0);
    auto delay = std::stoll(argv[5], nullptr, 0);

    if (count > 255 || count < 1)
    {
        cerr << "COUNT must be in range [1, 255]\n";
        return print_usage(argv[0]);
    }

    if (delay > 255 || delay < 1)
    {
        cerr << "DELAY must be in range [1, 255]\n";
        return print_usage(argv[0]);
    }

    run_test(node, value, increment, count, delay);
}
