#ifndef LIBHBP_CPP_TESTBASE_H
#define LIBHBP_CPP_TESTBASE_H

#include <extoll/extoll.h>

#include <vector>
#include <memory>


struct IFail
{
    virtual void report() = 0;
    virtual ~IFail() = default;
};

template <typename T>
struct Fail : IFail
{
    const char* message;
    T expected;
    T actual;

    Fail(const char*, T, T);
    void report() override;
};

struct TestFailedCritically : std::runtime_error
{
    using runtime_error::runtime_error;
};

class TestBase
{
    std::vector<std::unique_ptr<IFail>> fails;
    bool _critical = false;

    template <typename T>
    void fail(const char*, T, T, bool);
protected:
    extoll::library::Extoll& hbp;

    template <typename T>
    void critical(const char*, T expected, T actual);
    template <typename T>
    void warning(const char*, T expected, T actual);
public:
    explicit TestBase(extoll::library::Extoll&);
    virtual void run() = 0;
    void report();
    virtual ~TestBase() = default;

};


class Runner
{
    extoll::library::Extoll hbp{};
    std::vector<std::unique_ptr<TestBase>> tests{};

public:
    template<typename T, typename... Args>
    void add(Args&&...);
    void run();
};


template <typename T>
Fail<T>::Fail(const char* message, T expected, T actual)
    : message(message), expected(expected), actual(actual) {}

template <typename T>
void Fail<T>::report()
{
    std::cerr << "Fail: " << message << " incorrect\n";
    std::cerr << "  expected: " << expected << ", ";
    std::cerr << "got: " << actual << "\n";
}

template <typename T>
void TestBase::fail(const char* message, T expected, T actual, bool critical)
{
    if (expected != actual)
    {
        IFail* fail = new Fail<T>(message, expected, actual);
        std::unique_ptr<IFail> ptr(fail);
        fails.push_back(std::move(ptr));
        if (critical)
        {
            _critical = true;
            throw TestFailedCritically("");
        }
    }
}

template <typename T>
void TestBase::warning(const char* message, T expected, T actual)
{
    fail(message, expected, actual, false);
}

template <typename T>
void TestBase::critical(const char* message, T expected, T actual)
{
    fail(message, expected, actual, true);
}


template<typename T, typename... Args>
void Runner::add(Args&&... args)
{
    tests.emplace_back(new T(hbp, std::forward<Args>(args)...));
}




#endif //LIBHBP_CPP_TESTBASE_H
