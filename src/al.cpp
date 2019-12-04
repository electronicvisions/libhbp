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
        rf.write<TestControlMode>({0x1u});
        cout << "INFO: test mode is enabled: " << std::boolalpha << enabled() << "\n";
    }

    bool enabled()
    {
        auto mode = rf.read<TestControlMode>().mode();
        return (mode == 1) || (mode == 2);
    }

    ~TestMode()
    {
        cout << "INFO: waiting...\n";
        wait();
        rf.write<TestControlMode>({0});
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

void run_fpga_test(RMA2_Nodeid node, uint64_t value, bool increment, int64_t count, int64_t delay)
{
    auto rf = Extoll::Instance().register_file(node);
    auto fpga = Extoll::Instance().fpga(node);

    auto mode = rf.read<TestControlMode>().mode();
    if (mode == 1 || mode == 2)
    {
        cout << "WARNING: test mode was already enabled\n";
    }

    fpga.configure_partner_host();
    cout << "INFO: fpga put address: 0x" << hex << rf.read<ConfigResponse>().address() << "\n";

    rf.write<AlTestCounterReset>({true});

    {
        TestMode tm{rf};

        rf.write<TestControlType>({TestControlType::FpgaConfig});
        rf.write<TestControlData>({value});
        rf.write<TestControlConfig>({uint32_t(count), uint32_t(delay), increment});
        rf.write<TestControlStart>({true});
        std::cout << "INFO: started test run\n";

        while(rf.read<TestControlStart>().start())
        {
            std::cout << "INFO: still running\n";
            usleep(1000);
        }

        cout << "INFO: config response: " << fpga.config_response() << "\n";
    }

    cout << "INFO: any notifications?\n";

    rf.probe();
}

void run_test(RMA2_Nodeid node, uint64_t value, bool increment, int64_t count, int64_t delay,
TestControlType::Type type)
{
    auto rf = Extoll::Instance().register_file(node);
    auto fpga = Extoll::Instance().fpga(node);
    auto& buffer = (type == TestControlType::HicannConfig)? Extoll::Instance().hicann_config(node)
        : Extoll::Instance().trace_pulse(node);

    cout << "INFO: current version: " << rf.read<Version>().number() << "\n";

    auto mode = rf.read<TestControlMode>().mode();
    if (mode == 1 || mode == 2)
    {
        cout << "WARNING: test mode was already enabled\n";
    }

    fpga.configure_partner_host();
    std::cout << "INFO: host endpoint: 0x" << hex << rf.read<HostEndpoint>().raw << "\n";
    auto start_address = rf.read<HicannBufferCurrentAddress>().data();
    std::cout << "INFO: current address: 0x" << hex << start_address << "\n";

    rf.write<AlTestCounterReset>({true});

    std::vector<uint64_t> result;
    {
        TestMode tm{rf};

        rf.write<TestControlType>({type});
        rf.write<TestControlData>({value});
        rf.write<TestControlConfig>({uint32_t(count), uint32_t(delay), increment});
        rf.write<TestControlStart>({true});

        try
        {
            while (true)
            {
                auto v = buffer.get();
                result.push_back(v);
                //buffer.notify();
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "EXCEPTION: " << e.what() << "\n";
        }

        auto end_address = rf.read<HicannBufferCurrentAddress>().data();
        cout << "INFO: current address: 0x" << hex << end_address << "\n";
        cout << "INFO: difference: " << dec << end_address - start_address << "\n";
        cout << "INFO: result length: " << dec << result.size() << "\n";
        cout << "[";
        auto before = value - increment;
        bool increment_correct = true;
        for (auto& v : result)
        {
            cout << hex << v << " ";
            if (v != (before + increment))
            {
                increment_correct = false;
            }
            before = v;
        }
        cout << "\b]\n";
        cout << "INFO: increment correct: " << std::boolalpha << increment_correct << "\n";


        cout << "INFO: hicann config (s/r): ";
        cout << std::dec << rf.read<AlHicannConfigSent>().count() << " ";
        cout << std::dec << rf.read<AlHicannConfigReceived>().count() << "\n";
        cout << "INFO: fpga config   (s/r): ";
        cout << rf.read<AlFpgaConfigSent>().count() << " ";
        cout << rf.read<AlFpgaConfigReceived>().count() << "\n";
        cout << "INFO: jtag          (s/r): ";
        cout << rf.read<AlJtagSent>().count() << " ";
        cout << rf.read<AlJtagReceived>().count() << "\n";
        cout << "INFO: unknown type  (s/r): ";
        cout << rf.read<AlErrorUnknownTypeSent>().count() << " ";
        cout << rf.read<AlErrorUnknownTypeReceived>().count() << "\n";
        cout << "INFO: tracepulse/playback: ";
        cout << rf.read<AlTracePulseSent>().count() << " ";
        cout << rf.read<AlPlaybackDataReceived>().count() << "\n";
    }
}   

int print_usage(const char* program)
{
    cerr << "ERROR: usage: " << program << " NODE:int VALUE:uint INCREMENT:bool COUNT:int DELAY:int TYPE:str\n";
    return EXIT_FAILURE;
}

int main(int argc, char** argv)
{
    if (argc != 7)
    {
        return print_usage(argv[0]);
    }

    auto node = RMA2_Nodeid(std::stoi(argv[1], nullptr, 0));
    auto value = std::stoull(argv[2], nullptr, 0);
    auto type = std::string(argv[6]);
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

    if (delay > 255 || delay < 0)
    {
        cerr << "DELAY must be in range [0, 255]\n";
        return print_usage(argv[0]);
    }

    TestControlType::Type hex_type ;
    if (type == "hicann")
    {
        hex_type = TestControlType::HicannConfig;
    }
    else if (type == "trace")
    {
        hex_type = TestControlType::TracePulse;
    }
    else if (type == "fpga")
    {
        hex_type = TestControlType::FpgaConfig;
    }
    else {
        cerr << "TYPE must be either 'hicann', 'trace' or 'fpga'\n";
        return print_usage(argv[0]);
    }

    if (hex_type == TestControlType::FpgaConfig)
    {
        run_fpga_test(node, value, increment, count, delay);
    }
    else
    {
        run_test(node, value, increment, count, delay, hex_type);
    }
}
