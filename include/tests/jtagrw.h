#ifndef LIBHBP_CPP_JTAGRW_H
#define LIBHBP_CPP_JTAGRW_H

#include <extoll/rma.h>
#include <extoll/extoll.h>

#include "test.h"

class JtagRw : public TestBase
{

    RMA2_Nodeid node;
    uint8_t hicann_number;

public:
    JtagRw(extoll::library::Extoll&, RMA2_Nodeid, uint8_t);

    void run() override;
};

#endif //LIBHBP_CPP_JTAGRW_H
