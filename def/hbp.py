NAMESPACE = 'extoll', 'library', 'rf'
TEST_INCLUDE = '<extoll/hbp_def.h>'


# silence warnings
try:
    Address, ReadOnly, WriteOnly, ReadWrite
except NameError:
    def Address(a):
        class A:
            address = a
        return A

    class ReadOnly:
        pass

    class WriteOnly:
        pass

    class ReadWrite:
        pass


# Global Control
class Reset(Address(0x0), ReadWrite):
    core: 1
    hicann: 1
    arq: 1
    pulse_mem: 1


# Jtag Registers
class JtagCmd(Address(0x400), ReadWrite):
    type: 3
    length: 10
    pause: 1
    execute: 1

    class Type:
        Reset = 0b000
        IR = 0b001
        DR = 0b010
        EnableClock = 0b100
        DisableClock = 0b101


class JtagStatus(Address(0x408), ReadOnly):
    clock_enabled: 1
    paused: 1


class JtagSend(Address(0x480), ReadWrite):
    data: 64


class JtagReceive(Address(0x500), ReadOnly):
    data: 64


# Hicann Control Interface
class HicannIfState(Address(0x800), ReadOnly):
    channel_status: 8
    crc_count: 8
    systime: 14


class HicannIfRxConfig(Address(0x808), ReadOnly):
    data: 64


class HicannIfRxPulse(Address(0x810), ReadOnly):
    data: 24


class HicannIfConfig(Address(0x818), ReadWrite):
    start_link: 1
    loopback_enable: 1
    auto_init: 1
    init_master: 1
    use_timestamp: 1
    auto_limit: 1
    pulse_protocol: 1
    config_protocol: 1
    heap_mode: 8
    limit: 11
    dc_coding: 1


class HicannIfControls(Address(0x820), WriteOnly):
    tx_hicann_pulse_enable: 1
    tx_hicann_config_enable: 1
    routing_data_enable: 1
    channel_reset: 1
    crc_count_reset: 1


class HicannIfTxData(Address(0x828), ReadWrite):
    data: 64


class HicannPacketGen(Address(0x830), ReadWrite):
    count: 25
    error: 1
    enable: 1


class HicannChannel(Address(0x838), ReadWrite):
    number: 3


class ArqTimings(Address(0x840), ReadWrite):
    master_timeout: 10
    target_timeout: 10
    arbiter_delay: 5
    bit: 1


# Application Layer Test Interface
class TestControlEnable(Address(0xc00), ReadWrite):
    enable: 1


class TestControlConfig(Address(0xc08), ReadWrite):
    quad_words: 8
    pause_time: 8
    count_up: 1


class TestControlStart(Address(0xc10), ReadWrite):
    start: 1


class TestControlData(Address(0xc18), ReadWrite):
    data: 64


class TestControlType(Address(0xc20), ReadWrite):
    type: 16

    class Type:
        TracePulse = 0x0ca5
        FpgaConfig = 0x0c1b
        HicannConfig = 0x2a1b


# Trace Ringbuffer
class TraceBufferStart(Address(0x1000), ReadWrite):
    data: 64


class TraceBufferSize(Address(0x1008), ReadWrite):
    data: 32


class TraceBufferFullThreshold(Address(0x1010), ReadWrite):
    data: 32


class TraceBufferCounter(Address(0x1018), ReadOnly):
    start_address: 16
    size: 16
    threshold: 16
    wraps: 16


class TraceBufferCounterReset(Address(0x1020), WriteOnly):
    reset: 1


class TraceBufferCurrentAddress(Address(0x1028), ReadOnly):
    data: 64


class TraceBufferEndAddress(Address(0x1030), ReadOnly):
    data: 64


class TraceBufferFreeSpace(Address(0x1038), ReadOnly):
    data: 32


class TraceBufferInit(Address(0x1040), ReadWrite):
    start: 1


# Hicann Ringbuffer
class HicannBufferStart(Address(0x1080), ReadWrite):
    data: 64


class HicannBufferSize(Address(0x1088), ReadWrite):
    data: 32


class HicannBufferFullThreshold(Address(0x1090), ReadWrite):
    data: 32


class HicannBufferCounter(Address(0x1098), ReadOnly):
    start_address: 16
    size: 16
    threshold: 16
    wraps: 16


class HicannBufferCounterReset(Address(0x10a0), WriteOnly):
    reset: 1


class HicannBufferCurrentAddress(Address(0x10a8), ReadOnly):
    data: 64


class HicannBufferEndAddress(Address(0x10b0), ReadOnly):
    data: 64


class HicannBufferFreeSpace(Address(0x10b8), ReadOnly):
    data: 32


class HicannBufferInit(Address(0x10c0), ReadWrite):
    start: 1


# Performance Counter
class RraPutReceived(Address(0x1100), ReadOnly):
    count: 48


class RraGetReceived(Address(0x1108), ReadOnly):
    count: 48


class RmaPutReceived(Address(0x1110), ReadOnly):
    count: 48


class RmaNotificationReceived(Address(0x1118), ReadOnly):
    count: 48


class PlaybackReceived(Address(0x1120), ReadOnly):
    count: 48


class FpgaConfigReceived(Address(0x1128), ReadOnly):
    count: 48


class HicannConfigReceived(Address(0x1130), ReadOnly):
    count: 48


class JtagDataReceived(Address(0x1138), ReadOnly):
    count: 48


class NeighbourDataReceived(Address(0x1140), ReadOnly):
    count: 48


# Counter Reset
class CounterReset(Address(0x1148), WriteOnly):
    reset: 1


# Error Counters
class InvalidCommand(Address(0x1150), ReadOnly):
    count: 48


class InvalidType(Address(0x1158), ReadOnly):
    count: 48


class InvalidPayloadSize(Address(0x1160), ReadOnly):
    count: 48


class InvalidFields(Address(0x1168), ReadOnly):
    count: 48


class InvalidMode(Address(0x1170), ReadOnly):
    count: 48


class InvalidRraAddress(Address(0x1178), ReadOnly):
    count: 48


class InvalidHost(Address(0x1180), ReadOnly):
    count: 48


# Partner Host Configuration
class ConfigAddressReinit(Address(0x1188), ReadOnly):
    count: 48


class HostEndpoint(Address(0x1190), ReadWrite):
    node_id: 16
    protection_domain: 16
    vpid: 10
    mode: 6


class ConfigResponse(Address(0x1198), ReadWrite):
    address: 64


class TraceNotificationBehaviour(Address(0x11a0), ReadWrite):
    timeout: 32
    frequency: 32


class HicannNotificationBehaviour(Address(0x11a8), ReadWrite):
    timeout: 32
    frequency: 32


# Info Registers
class Driver(Address(0x8000), ReadOnly):
    version: 64


class Info(Address(0x8008), ReadOnly):
    guid: 24
    node_id: 16
