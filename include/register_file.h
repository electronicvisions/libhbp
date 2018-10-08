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
    HicannChannel = 0x838,
    HostEndpoint = 0x1090,
    TraceRingbufferStart = 0x1098,
    TraceRingbufferCapacity = 0x10a0,
    ResponseAddress = 0x10a8,
    HicannRingbufferStart = 0x10b0,
    HicannRingbufferCapacity = 0x10b8,
    TraceNotificationBehaviour = 0x10c0,
    HicannNotificationbehaviour = 0x10c8

};

enum class Writable
{

};

const ReadWrite HicannChannel = ReadWrite::HicannChannel;
}

class RegisterFile
{
protected:
    const Connection& connection;
    mutable RMA2_ERROR status;

public:
    explicit RegisterFile(const Connection&);

    uint64_t read(RMA2_NLA) const;
    uint64_t read(rf::Readable) const;
    uint64_t read(rf::ReadWrite) const;

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
