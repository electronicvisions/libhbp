#ifndef LIBHBP_CPP_WATCH_H
#define LIBHBP_CPP_WATCH_H

#include <extoll/rma.h>
#include <extoll/register_file.h>

namespace extoll {
namespace library {

constexpr static const RMA2_NLA WATCH_STATUS_ADDRESSES[8] = {
        0x1000, 0x1008, 0x1010, 0x1018,
        0x1020, 0x1028, 0x1030, 0x1040
};
constexpr static const RMA2_NLA WATCH_ERROR_ADDRESSES[7] = {
        0x1050, 0x1058, 0x1060, 0x1068, 0x1070, 0x1078, 0x1080
};
constexpr static const char * const WATCH_STATUS_NAMES[8] {
        "RRA put commands     ", "RRA get commands     ",
        "RMA put commands     ", "RMA Noti put commands",
        "Playback data packets", "FPGA config packets  ",
        "HICANN config packets", "Pulse data packets   ",
};
constexpr static const char * const WATCH_ERROR_NAMES[7] {
        "Error: Invalid commands    ", "Error: Invalid types       ",
        "Error: Invalid payload size", "Error: Fields error        ",
        "Error: Fields mode         ", "Error: Invalid RRA         ",
        "Error: Undefined host      "
};

struct Watch
{
    RegisterFile& rf;
    size_t registers;
    const RMA2_NLA* addresses;
    const char* const* const names;
    uint64_t before[8];
    bool compare_on_destruction = true;


    Watch(size_t registers, const RMA2_NLA* addresses, const char* const* const names, RegisterFile& rf)
            : rf(rf), registers(registers), addresses(addresses), names(names), before()
    {
        for (size_t i = 0; i < registers; ++i)
        {
            before[i] = rf.read(addresses[i]);
        }
    }

    void print()
    {
        compare_on_destruction = false;
        for (size_t i = 0; i < registers; ++i)
        {
            std::cout << std::dec << names[i] << ": " << rf.read(addresses[i]) << "\n";
        }
    }

    ~Watch()
    {
        if (!compare_on_destruction)
        {
            return;
        }

        for (size_t i = 0; i < 8; ++i)
        {
            auto now = rf.read(addresses[i]);
            if (now != before[i])
            {
                std::cout << std::dec << names[i] << ": " << before[i] << "->" << now << "\n";
            }
        }
    }
};

#define WATCH_STATUS extoll::library::Watch _s_(8, extoll::library::WATCH_STATUS_ADDRESSES, extoll::library::WATCH_STATUS_NAMES, *this);
#define WATCH_ERRORS extoll::library::Watch _e_(7, extoll::library::WATCH_ERROR_ADDRESSES, extoll::library::WATCH_ERROR_NAMES, *this);

#define WATCH_STATUS_FROM(RF) extoll::library::Watch _s_(8, extoll::library::WATCH_STATUS_ADDRESSES, extoll::library::WATCH_STATUS_NAMES, RF);
#define WATCH_ERRORS_FROM(RF) extoll::library::Watch _e_(7, extoll::library::WATCH_ERROR_ADDRESSES, extoll::library::WATCH_ERROR_NAMES, RF);


#define PRINT_STATUS_FROM(RF) extoll::library::Watch _ps_(8, extoll::library::WATCH_STATUS_ADDRESSES, extoll::library::WATCH_STATUS_NAMES, RF); _ps_.print();
#define PRINT_ERRORS_FROM(RF) extoll::library::Watch _pe_(7, extoll::library::WATCH_ERROR_ADDRESSES, extoll::library::WATCH_ERROR_NAMES, RF); _pe_.print();

}}

#endif //LIBHBP_CPP_WATCH_H
