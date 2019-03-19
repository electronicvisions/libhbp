#ifndef LIBHBP_CPP_RRA_H
#define LIBHBP_CPP_RRA_H

#include <utility>
#include <iostream>

#include <extoll/rma.h>
#include <extoll/connection.h>
#include <extoll/hbp_def.h>

namespace extoll {
namespace library {


class RegisterFile
{
protected:
    Endpoint& _connection;
    mutable RMA2_ERROR _status;

public:
    explicit RegisterFile(Endpoint&);
    RegisterFile(const RegisterFile&) = delete;
    RegisterFile(RegisterFile&&) noexcept = default;
    RegisterFile& operator=(const RegisterFile&) = delete;

    template <typename RF>
    RF read() const
    {
        static_assert(RF::ADDRESS >= 0, "register file address must be positive!");
        static_assert(RF::ADDRESS <= 0x180d0, "register file address too large!");
        static_assert(RF::READABLE, "register file must be readable!");

        RF rf;
        rf.raw = read(RF::ADDRESS);
        return rf;
    }

    template <typename RF>
    void write(RF&& rf)
    {
        static_assert(RF::ADDRESS >= 0, "register file address must be positive!");
        static_assert(RF::ADDRESS <= 0x180d0, "register file address too large!");
        static_assert(RF::WRITABLE, "register file must be writable!");

        write(RF::ADDRESS, rf.raw);
    }

    template <typename RF>
    void write_noblock(RF&& rf)
    {
        static_assert(RF::ADDRESS >= 0, "register file address must be positive!");
        static_assert(RF::ADDRESS <= 0x180d0, "register file address too large!");
        static_assert(RF::WRITABLE, "register file must be writable!");

        write_noblock(RF::ADDRESS, rf.raw);
    }

    uint64_t read(RMA2_NLA) const;

    void write_noblock(RMA2_NLA, uint64_t);
    void write(RMA2_NLA, uint64_t);

    void wait_for_notification() const;
    void wait_for_n_notifications(int) const;
    void wait_for_rma_notification(bool=false) const;

    bool probe() const;
};

}}

#endif
