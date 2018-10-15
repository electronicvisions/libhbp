#ifndef LIBHBP_CPP_TESTBASE_H
#define LIBHBP_CPP_TESTBASE_H

#include <hbp.h>

#include <vector>
#include <memory>

class TestBase
{
protected:
    HBP& hbp;
public:
    explicit TestBase(HBP&);
    virtual void run() = 0;
};


class Runner
{
    HBP hbp{};
    std::vector<std::unique_ptr<TestBase>> tests{};

public:
    template<typename T, typename... Args>
    void add(Args&&...);
    void run();
};

template<typename T, typename... Args>
void Runner::add(Args&&... args)
{
    tests.emplace_back(new T(hbp, std::forward<Args>(args)...));
}

#endif //LIBHBP_CPP_TESTBASE_H
