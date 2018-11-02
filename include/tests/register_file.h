#ifndef LIBHBP_CPP_TEST_REGISTER_FILE_H
#define LIBHBP_CPP_TEST_REGISTER_FILE_H

#include <rma.h>
#include <extoll.h>

#include "test.h"

class RegisterFileTest : public TestBase
{

    RMA2_Nodeid node;

public:
    RegisterFileTest(Extoll&, RMA2_Nodeid);

    void run() override;
};

#endif //LIBHBP_CPP_JTAGRW_H