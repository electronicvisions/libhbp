#ifndef LIBHBP_CPP_HICANN_H
#define LIBHBP_CPP_HICANN_H

#include <register_file.h>


class Hicann : public RegisterFile
{
    const static RMA2_NLA CONFIG_ADDRESS = 0x2a1bull << 48ull;

public:
    explicit Hicann(Endpoint&);

    void write(uint16_t address, uint32_t data);
    uint32_t read(uint16_t address);
};


#endif //LIBHBP_CPP_HICANN_H
