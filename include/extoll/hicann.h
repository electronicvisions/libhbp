#ifndef LIBHBP_CPP_HICANN_H
#define LIBHBP_CPP_HICANN_H

#include <extoll/register_file.h>

namespace extoll {
namespace library {

class Hicann : public RegisterFile
{
    const static RMA2_NLA CONFIG_ADDRESS = 0x2a1bull << 48ull;

    uint8_t number;


    void clear(PhysicalBuffer&, size_t=0);
    void diff(PhysicalBuffer&, size_t=0);
public:
    Hicann(Endpoint&, uint8_t);

    void write(uint16_t address, uint32_t data);
    uint32_t read(uint16_t address);

    void clear_all();
    void diff_all();
};

}}

#endif //LIBHBP_CPP_HICANN_H
