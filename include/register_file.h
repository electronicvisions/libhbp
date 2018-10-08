#ifndef LIBHBP_CPP_RRA_H
#define LIBHBP_CPP_RRA_H

#include <utility>

#include <rma.h>
#include <connection.h>
#include <register_files.h>


class RegisterFile
{
protected:
    const Connection& connection;
    mutable RMA2_ERROR status;

public:
    explicit RegisterFile(const Connection&);

    template <typename T>
    auto read() const -> typename traits::RfResultType<T>::value_type
    {
        static_assert(T::rf_address >= 0, "wat");
        static_assert(T::rf_address <= 0x180d0, "wat");

        using result_type = typename traits::RfResultType<T>::value_type;

        return result_type(read(T::rf_address));
    }
    uint64_t read(RMA2_NLA) const;
    uint64_t read(rf::Readable) const;
    uint64_t read(rf::ReadWrite) const;

    template <typename T, typename... Args>
    void write(Args&&... args)
    {
        static_assert(T::rf_address >= 0, "wat");
        static_assert(T::rf_address <= 0x180d0, "wat");

        T data(args...);
        write(T::rf_address, traits::rf_to_data(data));
    }

    template <typename T, typename... Args>
    void write_noblock(Args&&... args)
    {
        static_assert(T::rf_address >= 0, "wat");
        static_assert(T::rf_address <= 0x180d0, "wat");

        T data(args...);
        write_noblock(T::rf_address, traits::rf_to_data(data));
    }

    void write_noblock(RMA2_NLA, uint64_t);
    void write(RMA2_NLA, uint64_t);
    void write(rf::ReadWrite, uint64_t);

    void wait_for_notification() const;
    void wait_for_n_notifications(int) const;
protected:
    template <typename... Args>
    void throw_on_error(Args... args) const;
};


#endif
