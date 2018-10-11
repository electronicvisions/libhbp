#ifndef LIBHBP_CPP_JTAG_H
#define LIBHBP_CPP_JTAG_H

#include <bitset>

#include <register_file.h>

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

    void reset();
    void set_bypass();
    template <size_t S>
    std::bitset<S> shift_through(const char*);
    template <size_t S>
    std::bitset<S> shift_through(std::bitset<S>);

    uint64_t read(uint8_t);
    uint64_t read(jtag::Readable);
    uint64_t read(jtag::ReadWrite);


private:
    void wait_until_finished() const;

    friend std::ostream& operator<<(std::ostream&, const JTag&);
};

std::ostream& operator<<(std::ostream&, const JTag&);


template <size_t S>
std::bitset<S> JTag::shift_through(const char* pattern)
{
    return shift_through(std::bitset<S>(pattern));
}

template <size_t S>
std::bitset<S> JTag::shift_through(std::bitset<S> pattern)
{
    RegisterFile::write<JtagSend>(pattern.to_ullong());
    RegisterFile::write<JtagCmd>(JtagCmdType::DR, 64, false, true);
    wait_until_finished();

    return RegisterFile::read<JtagReceive>();
}

#endif
