#ifndef LIBHBP_CPP_RRA_H
#define LIBHBP_CPP_RRA_H

#include <utility>
#include <iostream>

#include <extoll/rma.h>
#include <extoll/connection.h>
#include <extoll/rf_definitions.h>

namespace extoll {
namespace library {


//! The remote register file access interface.
//! This class should be instantiated through the factory functions in Extoll
class RegisterFile
{
protected:
    //! A reference to the remote connection.
    //! Because of this reference, the class depends on the Extoll object that
    //! was used to create the register file interface.
    Endpoint& _connection;
    //! The status of the last `librma2` function.
    mutable RMA2_ERROR _status;

public:
    //! Create a register file interface from a given Endpoint.
    //! This constructor should not be used directly. Use the factory functions
    //! in Extoll instead.
    explicit RegisterFile(Endpoint&);
    //! This class is not copyable
    RegisterFile(const RegisterFile&) = delete;
    //! This class is movable
    RegisterFile(RegisterFile&&) noexcept = default;
    //! This class is not copy-assignable
    RegisterFile& operator=(const RegisterFile&) = delete;

    //! \brief Read the value of a register file.
    //!
    //! Only read-write or read-only register files can be used with this method.
    //! \code
    //! auto reset = rf.read<Reset>();
    //! std::cout << reset.core() << std::endl;
    //! \endcode
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

    //! \brief Write the value of a register file.
    //!
    //! Only read-write or write-only register files can be used with this method.
    //! \code
    //! rf.write<JtagCmd>({JtagCmd::IR, 6, false, true});
    //! \endcode
    template <typename RF>
    void write(RF&& rf)
    {
        static_assert(RF::ADDRESS >= 0, "register file address must be positive!");
        static_assert(RF::ADDRESS <= 0x180d0, "register file address too large!");
        static_assert(RF::WRITABLE, "register file must be writable!");

        write(RF::ADDRESS, rf.raw);
    }

    //! \brief Write the value of a register file, but don't wait for the notification.
    //!
    //! This method is identical to RegisterFile::write but it does not wait
    //! until the notification is received. Be sure to read the notification later
    //! with RegisterFile::wait_for_notification or RegisterFile::wait_for_n_notifications
    template <typename RF>
    void write_noblock(RF&& rf)
    {
        static_assert(RF::ADDRESS >= 0, "register file address must be positive!");
        static_assert(RF::ADDRESS <= 0x180d0, "register file address too large!");
        static_assert(RF::WRITABLE, "register file must be writable!");

        write_noblock(RF::ADDRESS, rf.raw);
    }

    //! \brief A non-template version of the read method.
    //!
    //! This method is untyped and neither checks whether the remote register file
    //! is readable nor does it unpack the bytes into the matching RF fields.
    uint64_t read(RMA2_NLA) const;

    uint64_t read_noblock(RMA2_NLA) const;

    //! \brief A non-template version of the write_noblock method.
    //!
    //! This method is untyped and neither checks whether the remote register file
    //! is writable nor does it provide a way to pack the fields into a quad word.
    void write_noblock(RMA2_NLA, uint64_t);
    //! \brief A non-template version of the write method.
    //!
    //! This method is untyped and neither checks whether the remote register file
    //! is writable nor does it provide a way to pack the fields into a quad word.
    void write(RMA2_NLA, uint64_t);

    //! \brief Wait for a single Rra notification.
    //!
    //! This method blocks until the notification has arrived
    void wait_for_notification() const;
    //! \brief Wait for multiple Rra notifications.
    //!
    //! This method blocks until all notifications have arrived.
    void wait_for_n_notifications(int count) const;
    //! \brief Wait for a single Rma notification.
    //!
    //! This method blocks until the notification has arrived.
    //! No public function in this class will trigger an Rma notification.
    void wait_for_rma_notification(bool=false) const;

    //! \brief Check if an Rra notification is there without blocking.
    //!
    //! This method does not consume the notification. Use `wait_for_notification`
    //! for that
    bool probe() const;
};

}}

#endif
