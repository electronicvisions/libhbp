NAMESPACE = 'extoll', 'library', 'jtag'
TEST_INCLUDE = '<extoll/jtag_definitions.h>'


# silence warnings
try:
    Address, Width, ReadOnly, WriteOnly, ReadWrite, Trigger
except NameError:
    def Address(a):
        class A:
            address = a
        return A
    
    def Width(a):
        class A:
            width = a
        return A

    class ReadOnly:
        pass

    class WriteOnly:
        pass

    class ReadWrite:
        pass
    
    class Trigger:
        pass


class ID(Address(0x00), Width(32), ReadOnly): pass
class Systime(Address(0x0b), Width(15), ReadOnly): pass
class RxData(Address(0x12), Width(64), ReadOnly): pass
class Status(Address(0x1a), Width(8), ReadOnly): pass
class CrcCount(Address(0x27), Width(8), ReadOnly): pass
class ArqTxPckNum(Address(0x31), Width(32), ReadOnly): pass
class ArqRxPckNum(Address(0x32), Width(32), ReadOnly): pass
class ArqRxDropNum(Address(0x33), Width(32), ReadOnly): pass
class ArqTxTimeoutNum(Address(0x36), Width(32), ReadOnly): pass
class ArqRxTimeoutNum(Address(0x37), Width(32), ReadOnly): pass

class LvdsPadsEnable(Address(0x02), Width(1), WriteOnly): pass
class LinkControl(Address(0x03), Width(9), WriteOnly): pass
class Layer1Mode(Address(0x04), Width(8), WriteOnly): pass
class SystemEnable(Address(0x05), Width(1), WriteOnly): pass
class BiasControl(Address(0x06), Width(6), WriteOnly): pass
class StopTimeCount(Address(0x0a), Width(1), WriteOnly): pass
class Set2Xpls(Address(0x0d), Width(1), WriteOnly): pass
class Pll2gControl(Address(0x10), Width(3), WriteOnly): pass
class TxData(Address(0x11), Width(64), WriteOnly): pass
class TestControl(Address(0x17), Width(4), WriteOnly): pass
class PllFarControl(Address(0x29), Width(15), WriteOnly): pass
class ArqControl(Address(0x30), Width(32), WriteOnly): pass
class ArqTxTimeoutValue(Address(0x34), Width(32), WriteOnly): pass
class ArqRxTimeoutValue(Address(0x35), Width(32), WriteOnly): pass

class IBias(Address(0x07), Width(15), ReadWrite): pass
class DelayRxData(Address(0x21), Width(6), ReadWrite): pass
class DelayRxClock(Address(0x22), Width(6), ReadWrite): pass

class StartLink(Address(0x08), Width(0), Trigger): pass
class StopLink(Address(0x09), Width(0), Trigger): pass
class StartConfigPackage(Address(0x18), Width(0), Trigger): pass
class StartPulsePackage(Address(0x19), Width(0), Trigger): pass
class SetReset(Address(0x1b), Width(0), Trigger): pass
class ReleaseReset(Address(0x1c), Width(0), Trigger): pass
class ResetCrcCount(Address(0x28), Width(0), Trigger): pass