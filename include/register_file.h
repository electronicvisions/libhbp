#ifndef LIBHBP_CPP_RRA_H
#define LIBHBP_CPP_RRA_H


#include <rma.h>
#include <connection.h>

namespace rf
{
enum class Readable
{
    Driver = 0x8000,
    Info = 0x8008
};

enum class ReadWrite
{
    HicannChannel = 0x838
};

enum class Writable
{

};

const Readable Driver = Readable::Driver;
const Readable Info = Readable::Info;

const ReadWrite HicannChannel = ReadWrite::HicannChannel;
}

class RegisterFile
{
protected:
    const Connection& connection;
    mutable RMA2_ERROR status;

public:
    explicit RegisterFile(const Connection&);

    uint64_t get(RMA2_NLA) const;
    uint64_t get(rf::Readable) const;
    uint64_t get(rf::ReadWrite) const;

    void set_noblock(RMA2_NLA, uint64_t);
    void set(RMA2_NLA, uint64_t);
    void set(rf::ReadWrite, uint64_t);

    void wait_for_notification() const;
    void wait_for_n_notifications(int) const;
protected:
    template <typename... Args>
    void throw_on_error(Args... args) const;
};


#endif
