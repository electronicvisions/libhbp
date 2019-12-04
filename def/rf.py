NAMESPACE = 'extoll', 'library', 'rf'
TEST_INCLUDE = '<extoll/rf_definitions.h>'


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
    """Resets certain components on the Fpga"""
    core: 1
    hicann: 1
    arq: 1
    pulse_mem: 1


# Jtag Registers
class JtagCmd(Address(0x400), ReadWrite):
    """
    The control register for the Jtag master controller.

    Type is the action that will be executed. Length specifies the number of
    shifts. Pause can be used when the data does not fit into the JtagSend RAM
    structure. Execute can be set to actually start the shifting process.

    Execute can be read to determine whether the shifting is done.

    Here is an example:
    \code
    // select a command register (bypass)
    rf.write<JtagSend>({0x3f});
    rf.write<JtagCmd>({JtagCmd::IR, 6, false, true});
    // wait until finished
    while (rf.read<JtagSend>().execute());
    // shift some data
    rf.write<JtagSend>({0xcafe});
    rf.write<JtagCmd>({JtagCmd::DR, 16, false, true});
    // wait until finished
    while (rf.read<JtagSend>().execute());
    // read the result
    std::cout << rf.read<JtagReceive>().data << std::endl;
    \endcode

    The JTag class encapsulates exactly that behaviour so it should be used instead.
    """
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
    """
    This register reports the status of the Jtag clock and the pause mode.
    As no known higher-level library neither uses the clock nor the pause bit,
    this will be rarely used.
    """
    clock_enabled: 1
    paused: 1


class JtagSend(Address(0x480), ReadWrite):
    """
    The data that will be shifted through the Jtag chain.
    There are actually 15 more of these registers at 0x488, 0x490, ..., 0x4f8
    """
    data: 64


class JtagReceive(Address(0x500), ReadOnly):
    """
    The data that was shifted out of the Jtag chain.
    There are actually 15 more of these registers at 0x508, 0x510, ..., 0x578
    """
    data: 64


# Hicann Control Interface
class HicannIfState(Address(0x800), ReadOnly):
    channel_status: 8
    crc_count: 8
    systime: 14
    init_state: 6
    rx_data: 8
    tx_data: 8


class SetHicannIfState(Address(0x808), ReadOnly):
    data_delay: 5
    data_delay_dout: 5


class HicannIfRxConfig(Address(0x810), ReadOnly):
    data: 64


class HicannIfRxPulse(Address(0x818), ReadOnly):
    data: 24


class HicannIfConfig(Address(0x820), ReadWrite):
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
    invert_deserializer_data: 1


class HicannIfControls(Address(0x828), WriteOnly):
    tx_hicann_pulse_enable: 1
    tx_hicann_config_enable: 1
    routing_data_enable: 1
    channel_reset: 1
    crc_count_reset: 1


class HicannIfTxData(Address(0x830), ReadWrite):
    """
    This register can be used to emulate highspeed packets via Jtag
    """
    data: 64


class HicannIfNeuronAddressFilter(Address(0x838), ReadWrite):
    negative_filter_mask: 9
    positive_filter_mask: 9


class HicannPacketGen(Address(0x840), ReadWrite):
    count: 25
    error: 1
    enable: 1


class HicannChannel(Address(0x848), ReadWrite):
    """
    This register selects the Hicann the Fpga will communicate with. Note, that
    the DNC order is expected here and not the Jtag order.
    """
    number: 3


class HicannTxIfPower(Address(0x868), ReadWrite):
    channel0: 2
    channel1: 2
    channel2: 2
    channel3: 2
    channel4: 2
    channel5: 2
    channel6: 2
    channel7: 2


# Application Layer Test Interface
class TestControlMode(Address(0xc00), ReadWrite):
    """
    This enabled the application layer test mode
    """
    mode: 2


class TestControlConfig(Address(0xc08), ReadWrite):
    """
    This configures an application layer test run. The number of quad words to send,
    the number of clock cycles to wait between each packet and whether to count
    up the value in the payload can be specified here.
    """
    quad_words: 8
    pause_time: 8
    count_up: 1


class TestControlStart(Address(0xc10), ReadWrite):
    """
    This starts an application layer test run.

    Writing a `1` will start the test. When the test is done, the hardware will
    reset the bit to zero.
    """
    start: 1


class TestControlData(Address(0xc18), ReadWrite):
    """
    The payload data that is send during the test runs.

    Use the count_up from the TestControlConfig to automatically increment it
    after each packet.
    """
    data: 64


class TestControlType(Address(0xc20), ReadWrite):
    """
    The payload type that is send during the test runs.

    These will be included in the notification class field.
    """
    type: 16

    class Type:
        UNDERLYING_TYPE = 'uint16_t'
        TracePulse = 0x0ca5
        FpgaConfig = 0x0c1b
        HicannConfig = 0x2a1b


class AlTestCounterReset(Address(0xc28), WriteOnly):
    reset: 1


class AlHicannConfigReceived(Address(0xc30), ReadOnly):
    count: 48


class AlFpgaConfigReceived(Address(0xc38), ReadOnly):
    count: 48


class AlPlaybackDataReceived(Address(0xc40), ReadOnly):
    count: 48


class AlJtagReceived(Address(0xc48), ReadOnly):
    count: 48


class AlErrorUnknownTypeReceived(Address(0xc50), ReadOnly):
    count: 48


class AlHicannConfigSent(Address(0xc58), ReadOnly):
    count: 48


class AlFpgaConfigSent(Address(0xc60), ReadOnly):
    count: 48


class AlTracePulseSent(Address(0xc68), ReadOnly):
    count: 48


class AlJtagSent(Address(0xc70), ReadOnly):
    count: 48


class AlErrorUnknownTypeSent(Address(0xc78),ReadOnly):
    count: 48


# Trace Ringbuffer
class TraceBufferStart(Address(0x1000), ReadWrite):
    """
    Address in bytes of the start of the trace-pulse data ringbuffer.

    This can be a physical or a logical address. For a logical address
    the HostEndpoint node must be set to `0x4`.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    data: 64


class TraceBufferSize(Address(0x1008), ReadWrite):
    """
    The capacity of the trace-pulse data ringbuffer in bytes.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    data: 32


class TraceBufferFullThreshold(Address(0x1010), ReadWrite):
    """
    The threshold that determines the full state of the trace-pulse data ringbuffer.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    data: 32


class TraceBufferCounter(Address(0x1018), ReadOnly):
    """
    Various counters that report the number of successful initializations of the
    trace-pulse data ringbuffer and the number of wrap arounds of the buffer.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    start_address: 16
    size: 16
    threshold: 16
    wraps: 16


class TraceBufferCounterReset(Address(0x1020), WriteOnly):
    """
    Writing a `1` will reset the start_address, size and threshold of TraceBufferCounter.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    reset: 1


class TraceBufferCurrentAddress(Address(0x1028), ReadOnly):
    """
    The address the hardware will send the next packet to.
    """
    data: 64


class TraceBufferEndAddress(Address(0x1030), ReadOnly):
    """
    The calculated end address of the trace-pulse data ringbuffer.
    """
    data: 64


class TraceBufferFreeSpace(Address(0x1038), ReadOnly):
    """
    The amount of free space inside the trace-pulse data ringbuffer in quad words.
    """
    data: 32


class TraceBufferInit(Address(0x1040), ReadWrite):
    """
    Writing a `1` will reconfigure the trace-pulse data ringbuffer according to
    the previously written config values.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    start: 1


# Hicann Ringbuffer
class HicannBufferStart(Address(0x1080), ReadWrite):
    """
    Address in bytes of the start of the hicann config data ringbuffer.

    This can be a physical or a logical address. For a logical address
    the HostEndpoint node must be set to `0x4`.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    data: 64


class HicannBufferSize(Address(0x1088), ReadWrite):
    """
    The capacity of the hicann config data ringbuffer in bytes.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    data: 32


class HicannBufferFullThreshold(Address(0x1090), ReadWrite):
    """
    The threshold that determines the full state of the hicann config data ringbuffer.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    data: 32


class HicannBufferCounter(Address(0x1098), ReadOnly):
    """
    Various counters that report the number of successful initializations of the
    hicann config data ringbuffer and the number of wrap arounds of the buffer.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    start_address: 16
    size: 16
    threshold: 16
    wraps: 16


class HicannBufferCounterReset(Address(0x10a0), WriteOnly):
    """
    Writing a `1` will reset the start_address, size and threshold of TraceBufferCounter.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    reset: 1


class HicannBufferCurrentAddress(Address(0x10a8), ReadOnly):
    """
    The address the hardware will send the next packet to.
    """
    data: 64


class HicannBufferEndAddress(Address(0x10b0), ReadOnly):
    """
    The calculated end address of the hicann config data ringbuffer.
    """
    data: 64


class HicannBufferFreeSpace(Address(0x10b8), ReadOnly):
    """
    The amount of free space inside the hicann config data ringbuffer in quad words.
    """
    data: 32


class HicannBufferInit(Address(0x10c0), ReadWrite):
    """
    Writing a `1` will reconfigure the hicann config data ringbuffer according to
    the previously written config values.

    For a high-level interface use the Fpga::configure_partner_host method.
    """
    start: 1


# Performance Counter
class RraPutReceived(Address(0x1100), ReadOnly):
    """
    Counts the number or register file write commands received
    """
    count: 48


class RraGetReceived(Address(0x1108), ReadOnly):
    """
    Counts the number of register file read commands received
    """
    count: 48


class RmaPutReceived(Address(0x1110), ReadOnly):
    """
    Counts the number of remote memory access commands received
    """
    count: 48


class RmaNotificationReceived(Address(0x1118), ReadOnly):
    """
    Counts the number of remote memory access notifications received
    """
    count: 48


class PlaybackReceived(Address(0x1120), ReadOnly):
    """
    Counts the number of received playback data packets
    """
    count: 48


class FpgaConfigReceived(Address(0x1128), ReadOnly):
    """
    Counts the number of Fpga config packets received.
    """
    count: 48


class HicannConfigReceived(Address(0x1130), ReadOnly):
    """
    Counts the number of Hicann config packets received.
    """
    count: 48


class JtagDataReceived(Address(0x1138), ReadOnly):
    """
    Counts the number of Jtag packets received.
    """
    count: 48


class NeighbourDataReceived(Address(0x1140), ReadOnly):
    """
    Counts the number of pulse routing packets from neighboring Fpgas.
    """
    count: 48


# Counter Reset
class CounterReset(Address(0x1148), WriteOnly):
    """
    Resets the following performance counters:
    - RraPutReceived
    - RraGetReceived
    - RmaPutReceived
    - RmaNotificationReceived
    - PlaybackReceived
    - FpgaConfigReceived
    - HicannConfigReceived
    - JtagDataReceived
    - NeighbourDataReceived

    And the following error counters:
    - InvalidCommand
    - InvalidType
    - InvalidPayloadSize
    - InvalidFields
    - InvalidMode
    - InvalidRraAddress
    - InvalidHost
    """
    reset: 1


# Error Counters
class InvalidCommand(Address(0x1150), ReadOnly):
    """
    Number of invalid commands received on Rma requests in completer.
    """
    count: 48


class InvalidType(Address(0x1158), ReadOnly):
    """
    Number of invalid payload-types received on Rma requests in completer.
    """
    count: 48


class InvalidPayloadSize(Address(0x1160), ReadOnly):
    """
    Number of invalid payload-sizes received on Rma requests in completer.
    """
    count: 48


class InvalidFields(Address(0x1168), ReadOnly):
    """
    Number of received Rma requests with marked error-fields in completer.
    """
    count: 48


class InvalidMode(Address(0x1170), ReadOnly):
    """
    Number of received Rma requests with error in mode-fields in completer.
    """
    count: 48


class InvalidRraAddress(Address(0x1208), ReadOnly):
    """
    Number of invalid Rra-addresses received.
    """
    count: 48


class ConfigAddressReinit(Address(0x1210), ReadOnly):
    """
    Number of attempts to reinit the host-addresses for fpga-config answers.

    Note: this is an error in the original register file documentation, but should
    actually be considered as a normal counter.
    """
    count: 48

# Responder Counters
class UndefinedHost(Address(0x1180), ReadOnly):
    """
    Number of attempts to send data to an unconfigured host.
    """
    count: 48


class RraGetResponsesSent(Address(0x1188), ReadOnly):
    """
    Number of RRA-get-responses sent in responder.
    """
    count: 48


class RmaPutRequestsSent(Address(0x1190), ReadOnly):
    """
    Number of RMA-put-requests sent in responder.
    """
    count: 48


class ReceiptNotificationPutRequestsSent(Address(0x1198), ReadOnly):
    """
    Number of RMA-notification-put-requests sent in responder
    """
    count: 48


class PayloadNotificationPutRequestsSent(Address(0x11a0), ReadOnly):
    """
    ...
    """
    count: 48


class TraceDataSent(Address(0x11a8), ReadOnly):
    """
    Number of Trace-Pulse-Data packets sent in responder.
    """
    count: 48


class FpagConfigSent(Address(0x11b0), ReadOnly):
    """
    Number of Fpga-Configuration packets sent in responder.
    """
    count: 48


class HicannConfigSent(Address(0x11b8), ReadOnly):
    """
    Number of Hicann-Configuration answer packets sent in responder.
    """
    count: 48


class JtagDataSent(Address(0x11c0), ReadOnly):
    """
    Number of Jtag-data packets sent in responder.
    """
    count: 48


class NeighbourPulseSend(Address(0x11c8), ReadOnly):
    """
    Number of Neighbour-Pulse-data packets sent in responder.
    """
    count: 48


class ResponderCounterReset(Address(0x11d0), WriteOnly):
    """
    Reset performance and error counters.
    """
    reset: 1

    count: 48


class NhtlCounterReset(Address(0x1200), WriteOnly):
    reset: 1


# Partner Host Configuration
class HostEndpoint(Address(0x1218), ReadWrite):
    """
    Configures the Fpga with data from the local node.

    The node id, protection domain and virtual process id all refer to the
    local host node. Mode must be set to `0x4` when any address is a logical
    address. It must be set to `0x0` when any address is a physical address.
    Therefor, it is not possible to mix logical and physical addresses.

    The addresses in question are:
    - TraceBufferStart
    - HicannBufferStart
    - ConfigResponse
    """
    node_id: 16
    protection_domain: 16
    vpid: 10
    mode: 6


class ConfigResponse(Address(0x1220), ReadWrite):
    """
    Address of the Fpga config response packets.

    This can be a physical or a logical address. For a logical address
    the HostEndpoint node must be set to `0x4`.
    """
    address: 64


class TraceNotificationBehaviour(Address(0x1228), ReadWrite):
    """
    The notification behavior of the trace-pulse data ringbuffer.

    Frequency is the number of packets after which the Fpga will send a payload
    notification to the host. Timeout specifies the number of clock cycles after
    which the Fpga will send a notification in case the number of packets is lower
    than the frequency.
    """
    timeout: 32
    frequency: 32


class HicannNotificationBehaviour(Address(0x1230), ReadWrite):
    """
    The notification behavior of the hicann config ringbuffer.

    Frequency is the number of packets after which the Fpga will send a payload
    notification to the host. Timeout specifies the number of clock cycles after
    which the Fpga will send a notification in case the number of packets is lower
    than the frequency.
    """
    timeout: 32
    frequency: 32

# Version Register
class Version(Address(0x4000), ReadOnly):
    """
    A static register file that contains the version number of the register-file.

    The version number will be incremented every time a change is made to the
    verilog register file definitions. This library will only work when the
    version number is exactly the same as expected.
    """
    number: 64

# Info Registers
class Driver(Address(0x8000), ReadOnly):
    """
    A static register file that contains the driver version of the Fpga.

    It is always `0xcafebabe`. This value is used internally to identify the
    Fpga. The implementation can only connect to a node with that exact driver
    version.
    """
    version: 64


class Info(Address(0x8008), ReadOnly):
    """
    Extoll specific information register.

    It contains a globally unique ID and the node id of the remote node.
    Note: it is possible that the node id is zero, when the Fpga have been
    flashed while the network is already running. In that case the node id could
    be written to the Fpga, as the register is actually read-write.
    """
    guid: 24
    node_id: 16
