#include "tests/test.h"

#include "tests/switchram.h"


TestBase::TestBase(HBP& hbp)
    : hbp(hbp) {}


void Runner::run()
{
    for (auto& test : tests)
    {
        test->run();
    }
}
