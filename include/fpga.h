#ifndef LIBHBP_CPP_FPGA_H
#define LIBHBP_CPP_FPGA_H

#include <register_file.h>

class Fpga : protected RegisterFile
{

public:
    using RegisterFile::RegisterFile;

    void reset();
    void configure_partner_host();
};


#endif //LIBHBP_CPP_FPGA_H
