#ifndef LIBHBP_CPP_JTAG_H
#define LIBHBP_CPP_JTAG_H


#include "register_file.h"

namespace jtag
{
enum class Readable
{
    ID = 0x00,
    Systime = 0x0b,
    RxData = 0x12,
    Status = 0x1a,
    CrcCount = 0x27,
    ArqTxPckNum = 0x31,
    ArqRxPckNum = 0x32,
    ArqRxDropNum = 0x33,
    ArqTxTimeoutNum = 0x36,
    ArqRxTimeoutNum = 0x37
};

enum class ReadWrite
{
    DelayRxData = 0x21
};

enum class Writable
{
    SystemEnable = 0x05
};

const Readable ID = Readable::ID;
const Readable Systime = Readable::Systime;
const Readable RxData = Readable::RxData;
const Readable Status = Readable::Status;
const Readable CrcCount = Readable::CrcCount;
const Readable ArqTxPckNum = Readable::ArqTxPckNum;
const Readable ArqRxPckNum = Readable::ArqRxPckNum;
const Readable ArqRxDropNum = Readable::ArqRxDropNum;
const Readable ArqTxTimeoutNum = Readable::ArqTxTimeoutNum;
const Readable ArqRxTimeoutNum = Readable::ArqRxTimeoutNum;

const ReadWrite DelayRxData = ReadWrite::DelayRxData;

const Writable SystemEnable = Writable::SystemEnable;
}


class JTag : protected RegisterFile
{

public:
    using RegisterFile::RegisterFile;

    uint64_t get(uint8_t);
    uint64_t get(jtag::Readable);
    uint64_t get(jtag::ReadWrite);

    void set(uint8_t, uint64_t);
    void set(jtag::ReadWrite, uint64_t);
    void set(jtag::Writable, uint64_t);

    void reset();
private:
    void wait_until_finished() const;

};


#endif
