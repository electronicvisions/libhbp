#include <tests/test.h>

#include "tests/test.h"

#include "tests/switchram.h"


TestBase::TestBase(extoll::library::Extoll& hbp)
    : hbp(hbp) {}

void TestBase::report()
{

    if (fails.empty())
    {
        std::clog << "Test Passed\n";
    }
    else if(!_critical)
    {
        std::clog << "Test Passed With Errors\n";
    }
    for (auto& f : fails)
    {
        f->report();
    }
}

void Runner::run()
{
    for (auto& test : tests)
    {
        try
        {
            test->run();
        }
        catch (TestFailedCritically& e)
        {
            std::cerr << "Test Failed Critically\n";
        }

        test->report();
    }
}
