#ifndef LIBHBP_CPP_EXCEPTION_H
#define LIBHBP_CPP_EXCEPTION_H

#include <stdexcept>

struct BufferError : std::runtime_error {
    explicit BufferError(const char* msg) : std::runtime_error(msg) {}
};

struct RMAError : std::runtime_error {
    explicit RMAError(const char* msg) : std::runtime_error(msg) {}
    explicit RMAError(std::string&& msg) : std::runtime_error(msg) {}
};

struct ConnectionError : std::runtime_error {
    explicit ConnectionError(const char* msg) : std::runtime_error(msg) {}
    explicit ConnectionError(std::string&& msg) : std::runtime_error(msg) {}
};

#endif //LIBHBP_CPP_EXCEPTION_H
