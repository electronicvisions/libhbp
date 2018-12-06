NAMESPACE = 'extoll', 'library', 'rf'


class Reset(Address(0x0), ReadWrite):
    core: 1
    hicann: 1
    arq: 1


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
    clock_enabled: 1;
    paused: 1;


class JtagSend(Address(0x480), ReadWrite):
    data: 64


class JtagReceive(Address(0x500), ReadOnly):
    data: 64


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


class HostEndpoint(Address(0x1090), ReadWrite):
    node_id: 16
    protection_domain: 16
    vpid: 10
    mode: 6


class TraceRingbufferStart(Address(0x1098), ReadWrite):
    address: 64


class TraceRingbufferCapacity(Address(0x10a0), ReadWrite):
    capacity: 32
    start_change_counter: 8
    capacity_change_counter: 8
    init: 1


class ConfigResponse(Address(0x10a8), ReadWrite):
    address: 64


class HicannRingbufferStart(Address(0x10b0), ReadWrite):
    address: 64


class HicannRingbufferCapacity(Address(0x10b8), ReadWrite):
    capacity: 32
    start_change_counter: 8
    capacity_change_counter: 8
    init: 1


class TraceNotificationBehaviour(Address(0x10c0), ReadWrite):
    timeout: 32
    frequency: 32


class HicannNotificationBehaviour(Address(0x10c8), ReadWrite):
    timeout: 32
    frequency: 32


class Driver(Address(0x8000), ReadOnly):
    version: 64


class Info(Address(0x8008), ReadOnly):
    guid: 24
    node_id: 16
