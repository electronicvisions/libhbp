#ifndef LIBHBP_CPP_JTAG_REGISTERS_H
#define LIBHBP_CPP_JTAG_REGISTERS_H

#include <cinttypes>

#define READ 1
#define WRITE 2
#define READWRITE 3
#define TRIG 4

#define JTAG_REGISTER(_NAME, _ADDRESS, _SIZE, RWT)\
struct _NAME {\
    constexpr const static char * const NAME = #_NAME;\
    const static uint64_t ADDRESS = _ADDRESS;\
    const static bool READABLE = (1 & RWT) > 0;\
    const static bool WRITABLE = (2 & RWT) > 0;\
    const static bool TRIGGER = (4 & RWT) > 0;\
    const static uint64_t SIZE = _SIZE;\
    const static uint64_t MASK = (_SIZE == 64)? 0xffffffffffffffff : ((1ull << _SIZE) - 1ull);\
    \
};

namespace jtag{

JTAG_REGISTER(ID, 0x00, 32, READ)
JTAG_REGISTER(Systime, 0x0b, 15, READ)
JTAG_REGISTER(RxData, 0x12, 64, READ)
JTAG_REGISTER(Status, 0x1a, 8, READ)
JTAG_REGISTER(CrcCount, 0x27, 8, READ)
JTAG_REGISTER(ArqTxPckNum, 0x31, 32, READ)
JTAG_REGISTER(ArqRxPckNum, 0x32, 32, READ)
JTAG_REGISTER(ArqRxDropNum, 0x33, 32, READ)
JTAG_REGISTER(ArqTxTimeoutNum, 0x36, 32, READ)
JTAG_REGISTER(ArqRxTimeoutNum, 0x37, 32, READ)

JTAG_REGISTER(LvdsPadsEnable, 0x02, 1, WRITE)
JTAG_REGISTER(LinkControl, 0x03, 9, WRITE)
JTAG_REGISTER(Layer1Mode, 0x04, 8, WRITE)
JTAG_REGISTER(SystemEnable, 0x05, 1, WRITE)
JTAG_REGISTER(BiasControl, 0x06, 6, WRITE)
JTAG_REGISTER(StopTimeCount, 0x06, 1, WRITE)
JTAG_REGISTER(Set2Xpls, 0x0d, 1, WRITE)
JTAG_REGISTER(Pll2gControl, 0x10, 3, WRITE)
JTAG_REGISTER(TxData, 0x11, 64, WRITE)
JTAG_REGISTER(TestControl, 0x17, 4, WRITE)
JTAG_REGISTER(PllFarControl, 0x29, 15, WRITE)
JTAG_REGISTER(ArqControl, 0x30, 32, WRITE)
JTAG_REGISTER(ArqTxTimeoutValue, 0x34, 32, WRITE)
JTAG_REGISTER(ArqRxTimeoutValue, 0x35, 32, WRITE)

JTAG_REGISTER(IBias, 0x07, 15, READWRITE)
JTAG_REGISTER(DelayRxData, 0x21, 6, READWRITE)
JTAG_REGISTER(DelayRxClock, 0x22, 6, READWRITE)

JTAG_REGISTER(StartLink, 0x08, 0, TRIG)
JTAG_REGISTER(StopLink, 0x09, 0, TRIG)
JTAG_REGISTER(StartConfigPackege, 0x18, 0, TRIG)
JTAG_REGISTER(StartPulsePackage, 0x19, 0, TRIG)
JTAG_REGISTER(SetReset, 0x1b, 0, TRIG)
JTAG_REGISTER(ReleaseReset, 0x1c, 0, TRIG)
JTAG_REGISTER(ResetCrcCount, 0x28, 0, TRIG)

}

#undef READ
#undef WRITE
#undef READWRITE
#undef TRIG
#undef JTAG_REGISTER

#endif //LIBHBP_CPP_JTAG_REGISTERS_H
