#ifndef LIBHBP_CPP_SWITCHRAM_H
#define LIBHBP_CPP_SWITCHRAM_H

#include <rma.h>
#include <hbp.h>

#include "test.h"

class SwitchRam : public TestBase
{

    RMA2_Nodeid node;
    uint8_t hicann_number;

public:
    SwitchRam(HBP&, RMA2_Nodeid, uint8_t);

    void run() override;
};


#endif //LIBHBP_CPP_SWITCHRAM_H
