#ifndef LIBHBP_CPP_JTAG_H
#define LIBHBP_CPP_JTAG_H

#include <bitset>

#include <register_file.h>

#define EXPOSER(MEMBER) const Readable MEMBER = Readable::MEMBER
#define EXPOSEW(MEMBER) const Writable MEMBER = Writable::MEMBER

namespace jtag
{
enum class Readable : uint8_t
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
    ArqRxTimeoutNum = 0x37,
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

enum class Writable : uint8_t
{
    LvdsPadsEnable = 0x02,
    LinkControl = 0x03,
    Layer1Mode = 0x04,
    SystemEnable = 0x05,
    BiasControl = 0x06,
    StopTimeCount = 0x0a,
    Set2Xpls = 0x0d,
    Pll2gControl = 0x10,
    TxData = 0x11,
    TestControl = 0x17,
    PllFarControl = 0x29,
    ArqControl = 0x30,
    ArqTxTimeoutValue = 0x34,
    ArqRxTimeoutValue = 0x35,
};

const Writable LvdsPadsEnable = Writable::LvdsPadsEnable;
const Writable LinkControl = Writable::LinkControl;
const Writable Layer1Mode = Writable::Layer1Mode;
const Writable SystemEnable = Writable::SystemEnable;
const Writable BiasControl = Writable::BiasControl;
const Writable StopTimeCount = Writable::StopTimeCount;
const Writable Set2Xpls = Writable::Set2Xpls;
const Writable Pll2gControl = Writable::Pll2gControl;
const Writable TxData = Writable::TxData;
const Writable TestControl = Writable::TestControl;
const Writable PllFarControl = Writable::PllFarControl;
const Writable ArqControl = Writable::ArqControl;
const Writable ArqTxTimeoutValue = Writable::ArqTxTimeoutValue;
const Writable ArqRxTimeoutValue = Writable::ArqRxTimeoutValue;

enum class ReadWrite : uint8_t
{
    IBias = 0x07,
    DelayRxData = 0x21,
    DelayRxClock = 0x22,
};

const ReadWrite IBias = ReadWrite::IBias;
const ReadWrite DelayRxData = ReadWrite::DelayRxData;
const ReadWrite DelayRxClock = ReadWrite::DelayRxClock;

enum class Trigger : uint8_t
{
    StartLink = 0x08,
    StopLink = 0x09,
    StartConfigPackage = 0x18,
    StartPulsePackage = 0x19,
    SetReset = 0x1b,
    ReleaseReset = 0x1c,
    ResetCrcCount = 0x28,
};

const Trigger StartLink = Trigger::StartLink;
const Trigger StopLink = Trigger::StopLink;
const Trigger StartConfigPackage = Trigger::StartConfigPackage;
const Trigger StartPulsePackage = Trigger::StartPulsePackage;
const Trigger SetReset = Trigger::SetReset;
const Trigger ReleaseReset = Trigger::ReleaseReset;
const Trigger ResetCrcCount = Trigger::ResetCrcCount;

}


class JTag : protected RegisterFile
{

public:
    explicit JTag(Endpoint&);

    void reset();
    void set_bypass();
    template <size_t S>
    std::bitset<S> shift_through(const char*, uint16_t length=64);
    template <size_t S>
    std::bitset<S> shift_through(std::bitset<S>, uint16_t length=64);


    uint64_t read(jtag::Readable);
    void write(jtag::Writable, uint64_t);
    uint64_t read_write(jtag::ReadWrite, uint64_t);
    void trigger(jtag::Trigger);


private:
    void wait_until_finished() const;

    friend std::ostream& operator<<(std::ostream&, const JTag&);
};

std::ostream& operator<<(std::ostream&, const JTag&);


template <size_t S>
std::bitset<S> JTag::shift_through(const char* pattern, uint16_t length)
{
    return shift_through(std::bitset<S>(pattern), length);
}

template <size_t S>
std::bitset<S> JTag::shift_through(std::bitset<S> pattern, uint16_t length)
{
    using namespace rf;

    RegisterFile::write<JtagSend>({pattern.to_ullong()});
    RegisterFile::write<JtagCmd>({JtagCmd::Type::DR, length, false, true});
    wait_until_finished();

    return RegisterFile::read(JtagReceive::ADDRESS);
}

#endif
