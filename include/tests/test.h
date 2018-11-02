#ifndef LIBHBP_CPP_TESTBASE_H
#define LIBHBP_CPP_TESTBASE_H

#include <extoll.h>

#include <vector>
#include <memory>

class TestBase
{
protected:
    Extoll& hbp;
public:
    explicit TestBase(Extoll&);
    virtual void run() = 0;
    virtual ~TestBase() = default;
};


class Runner
{
    Extoll hbp{};
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
