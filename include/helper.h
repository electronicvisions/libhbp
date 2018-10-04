#ifndef LIBHBP_CPP_HELPER_H
#define LIBHBP_CPP_HELPER_H

#include <rma.h>
#include <sstream>

template <typename T>
static void stream(std::ostream& out, T value)
{
    out << value;
}

template <typename T, typename... Args>
static void stream(std::ostream& out, T value, Args... args)
{
    out << value;
    stream(out, args...);
}

template<typename E, typename... Args>
void throw_on_error(RMA2_ERROR status, Args... args)
{
    if (status != RMA2_SUCCESS)
    {
        std::stringstream s;
        stream(s, args...);

        throw E{s.str()};
    }

}

template<typename E, typename... Args>
void throw_now(Args... args)
{
    std::stringstream s;
    stream(s, args...);

    throw E{s.str()};
}

#endif //LIBHBP_CPP_HELPER_H
