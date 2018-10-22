#ifndef LIBHBP_CPP_RRA_H
#define LIBHBP_CPP_RRA_H

#include <utility>

#include <rma.h>
#include <connection.h>
#include <register_files.h>


class RegisterFile
{
protected:
    Endpoint& connection;
    mutable RMA2_ERROR status;

public:
    explicit RegisterFile(Endpoint&);

    template <typename RF>
    RF read() const
    {
        static_assert(RF::ADDRESS >= 0, "register file address must be positive!");
        static_assert(RF::ADDRESS <= 0x180d0, "register file address too large!");
        static_assert(RF::READABLE, "register file must be readable!");

        return rf::data_to_rf<RF>(read(RF::ADDRESS));
    }

    template <typename RF>
    void write(RF&& rf)
    {
        static_assert(RF::ADDRESS >= 0, "register file address must be positive!");
        static_assert(RF::ADDRESS <= 0x180d0, "register file address too large!");
        static_assert(RF::WRITABLE, "register file must be writable!");

        write(RF::ADDRESS, rf::rf_to_data(std::forward<RF>(rf)));
    }

    template <typename RF>
    void write_noblock(RF&& rf)
    {
        static_assert(RF::ADDRESS >= 0, "register file address must be positive!");
        static_assert(RF::ADDRESS <= 0x180d0, "register file address too large!");
        static_assert(RF::WRITABLE, "register file must be writable!");

        write_noblock(RF::ADDRESS, rf::rf_to_data(std::forward<RF>(rf)));
    }

    uint64_t read(RMA2_NLA) const;

    void write_noblock(RMA2_NLA, uint64_t);
    void write(RMA2_NLA, uint64_t);

    void wait_for_notification() const;
    void wait_for_n_notifications(int) const;
    void wait_for_rma_notification(bool=false) const;

    void probe() const;
};


#endif
