#ifndef LIBHBP_CPP_APPLICATION_PROTOCOL_H
#define LIBHBP_CPP_APPLICATION_PROTOCOL_H

#include <cinttypes>
#include <iostream>

#include <extoll/extoll.h>

uint8_t dnc_index(extoll::library::JTag& jtag, uint8_t hicann);

void highspeed_init(
    extoll::library::RegisterFile& rf,
    extoll::library::JTag& jtag,
    extoll::library::Fpga& fpga,
    uint8_t hicann);

struct HsStatus
{
	bool fpga_ok;
	bool hicann_ok;
};

HsStatus highspeed_status(
    extoll::library::RegisterFile& rf, extoll::library::JTag& jtag, uint8_t hicann);

std::ostream& operator<<(std::ostream& out, const HsStatus& status);

#endif // LIBHBP_CPP_APPLICATION_PROTOCOL_H
