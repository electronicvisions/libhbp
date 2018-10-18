#ifndef LIBHBP_CPP_WATCH_H
#define LIBHBP_CPP_WATCH_H

#include <rma.h>
#include <register_file.h>

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

struct _Watch
{
    RegisterFile& rf;
    size_t registers;
    const RMA2_NLA* addresses;
    const char* const* const names;
    uint64_t before[8];


    _Watch(size_t registers, const RMA2_NLA* addresses, const char* const* const names, RegisterFile& rf)
            : rf(rf), registers(registers), addresses(addresses), names(names), before()
    {
        for (size_t i = 0; i < registers; ++i)
        {
            before[i] = rf.read(addresses[i]);
        }
    }

    ~_Watch()
    {
        for (size_t i = 0; i < 8; ++i)
        {
            auto now = rf.read(addresses[i]);
            if (now != before[i])
            {
                std::cout << names[i] << ": " << before[i] << "->" << now << "\n";
            }
        }
    }
};

#define WATCH_STATUS _Watch _s_(8, WATCH_STATUS_ADDRESSES, WATCH_STATUS_NAMES, *this);
#define WATCH_ERRORS _Watch _e_(7, WATCH_ERROR_ADDRESSES, WATCH_ERROR_NAMES, *this);


#endif //LIBHBP_CPP_WATCH_H
