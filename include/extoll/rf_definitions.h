/*
 * This is a generated file - do not change it
 * 2019-12-16 13:35:42.231572
 */

#pragma once

#include <cinttypes>

#include <extoll/rma.h>


namespace extoll {
namespace library {
namespace rf {



//! Read-write register file Reset at address 0x0.
//! Resets certain components on the Fpga
struct Reset
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    Reset() = default;

    //! Initialize all fields with a specific value
    Reset(bool core_, bool hicann_, bool arq_, bool pulse_mem_)
    {
        raw |= (uint64_t(core_) & 0x1) << 0;
        raw |= (uint64_t(hicann_) & 0x1) << 1;
        raw |= (uint64_t(arq_) & 0x1) << 2;
        raw |= (uint64_t(pulse_mem_) & 0x1) << 3;
    }
    
    //! Read the `core` field
    bool core() const { return bool(raw >> 0 & 0x1);}
    //! Read the `hicann` field
    bool hicann() const { return bool(raw >> 1 & 0x1);}
    //! Read the `arq` field
    bool arq() const { return bool(raw >> 2 & 0x1);}
    //! Read the `pulse_mem` field
    bool pulse_mem() const { return bool(raw >> 3 & 0x1);}

    
    //! Set the `core` field
    void core(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    //! Set the `hicann` field
    void hicann(bool value) { raw &= ~(0x1ull << 1); raw |= (uint64_t(value) & 0x1) << 1;}
    //! Set the `arq` field
    void arq(bool value) { raw &= ~(0x1ull << 2); raw |= (uint64_t(value) & 0x1) << 2;}
    //! Set the `pulse_mem` field
    void pulse_mem(bool value) { raw &= ~(0x1ull << 3); raw |= (uint64_t(value) & 0x1) << 3;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x0;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file JtagCmd at address 0x400.
//! The control register for the Jtag master controller.
//! 
//! Type is the action that will be executed. Length specifies the number of
//! shifts. Pause can be used when the data does not fit into the JtagSend RAM
//! structure. Execute can be set to actually start the shifting process.
//! 
//! Execute can be read to determine whether the shifting is done.
//! 
//! Here is an example:
//! \code
//! // select a command register (bypass)
//! rf.write<JtagSend>({0x3f});
//! rf.write<JtagCmd>({JtagCmd::IR, 6, false, true});
//! // wait until finished
//! while (rf.read<JtagSend>().execute());
//! // shift some data
//! rf.write<JtagSend>({0xcafe});
//! rf.write<JtagCmd>({JtagCmd::DR, 16, false, true});
//! // wait until finished
//! while (rf.read<JtagSend>().execute());
//! // read the result
//! std::cout << rf.read<JtagReceive>().data << std::endl;
//! \endcode
//! 
//! The JTag class encapsulates exactly that behaviour so it should be used instead.
struct JtagCmd
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;
    //! All possible values for the `type` field.
    enum class Type
    {
        Reset = 0,
        IR = 1,
        DR = 2,
        EnableClock = 4,
        DisableClock = 5,
    };
    //! Convenience alias for the `Type` enum
    constexpr static Type Reset = Type::Reset;
    //! Convenience alias for the `Type` enum
    constexpr static Type IR = Type::IR;
    //! Convenience alias for the `Type` enum
    constexpr static Type DR = Type::DR;
    //! Convenience alias for the `Type` enum
    constexpr static Type EnableClock = Type::EnableClock;
    //! Convenience alias for the `Type` enum
    constexpr static Type DisableClock = Type::DisableClock;

    //! Initialize all fields with zero
    JtagCmd() = default;

    //! Initialize all fields with a specific value
    JtagCmd(Type type_, uint32_t length_, bool pause_, bool execute_)
    {
        raw |= (uint64_t(type_) & 0x7) << 0;
        raw |= (uint64_t(length_) & 0x3ff) << 3;
        raw |= (uint64_t(pause_) & 0x1) << 13;
        raw |= (uint64_t(execute_) & 0x1) << 14;
    }
    
    //! Read the `type` field
    Type type() const { return Type(raw >> 0 & 0x7);}
    //! Read the `length` field
    uint32_t length() const { return uint32_t(raw >> 3 & 0x3ff);}
    //! Read the `pause` field
    bool pause() const { return bool(raw >> 13 & 0x1);}
    //! Read the `execute` field
    bool execute() const { return bool(raw >> 14 & 0x1);}

    
    //! Set the `type` field
    void type(Type value) { raw &= ~(0x7ull << 0); raw |= (uint64_t(value) & 0x7) << 0;}
    //! Set the `length` field
    void length(uint32_t value) { raw &= ~(0x3ffull << 3); raw |= (uint64_t(value) & 0x3ff) << 3;}
    //! Set the `pause` field
    void pause(bool value) { raw &= ~(0x1ull << 13); raw |= (uint64_t(value) & 0x1) << 13;}
    //! Set the `execute` field
    void execute(bool value) { raw &= ~(0x1ull << 14); raw |= (uint64_t(value) & 0x1) << 14;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x400;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file JtagStatus at address 0x408.
//! This register reports the status of the Jtag clock and the pause mode.
//! As no known higher-level library neither uses the clock nor the pause bit,
//! this will be rarely used.
struct JtagStatus
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    JtagStatus() = default;

    //! Initialize all fields with a specific value
    JtagStatus(bool clock_enabled_, bool paused_)
    {
        raw |= (uint64_t(clock_enabled_) & 0x1) << 0;
        raw |= (uint64_t(paused_) & 0x1) << 1;
    }
    
    //! Read the `clock_enabled` field
    bool clock_enabled() const { return bool(raw >> 0 & 0x1);}
    //! Read the `paused` field
    bool paused() const { return bool(raw >> 1 & 0x1);}

    
    //! Set the `clock_enabled` field
    void clock_enabled(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    //! Set the `paused` field
    void paused(bool value) { raw &= ~(0x1ull << 1); raw |= (uint64_t(value) & 0x1) << 1;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x408;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-write register file JtagSend at address 0x480.
//! The data that will be shifted through the Jtag chain.
//! There are actually 15 more of these registers at 0x488, 0x490, ..., 0x4f8
struct JtagSend
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    JtagSend() = default;
    //! Initialize the single field with a specific value
    JtagSend(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x480;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file JtagReceive at address 0x500.
//! The data that was shifted out of the Jtag chain.
//! There are actually 15 more of these registers at 0x508, 0x510, ..., 0x578
struct JtagReceive
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    JtagReceive() = default;
    //! Initialize the single field with a specific value
    JtagReceive(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x500;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file HicannIfState at address 0x800.
struct HicannIfState
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannIfState() = default;

    //! Initialize all fields with a specific value
    HicannIfState(uint32_t channel_status_, uint32_t crc_count_, uint32_t systime_, uint32_t init_state_, uint32_t rx_data_, uint32_t tx_data_)
    {
        raw |= (uint64_t(channel_status_) & 0xff) << 0;
        raw |= (uint64_t(crc_count_) & 0xff) << 8;
        raw |= (uint64_t(systime_) & 0x3fff) << 16;
        raw |= (uint64_t(init_state_) & 0x3f) << 30;
        raw |= (uint64_t(rx_data_) & 0xff) << 36;
        raw |= (uint64_t(tx_data_) & 0xff) << 44;
    }
    
    //! Read the `channel_status` field
    uint32_t channel_status() const { return uint32_t(raw >> 0 & 0xff);}
    //! Read the `crc_count` field
    uint32_t crc_count() const { return uint32_t(raw >> 8 & 0xff);}
    //! Read the `systime` field
    uint32_t systime() const { return uint32_t(raw >> 16 & 0x3fff);}
    //! Read the `init_state` field
    uint32_t init_state() const { return uint32_t(raw >> 30 & 0x3f);}
    //! Read the `rx_data` field
    uint32_t rx_data() const { return uint32_t(raw >> 36 & 0xff);}
    //! Read the `tx_data` field
    uint32_t tx_data() const { return uint32_t(raw >> 44 & 0xff);}

    
    //! Set the `channel_status` field
    void channel_status(uint32_t value) { raw &= ~(0xffull << 0); raw |= (uint64_t(value) & 0xff) << 0;}
    //! Set the `crc_count` field
    void crc_count(uint32_t value) { raw &= ~(0xffull << 8); raw |= (uint64_t(value) & 0xff) << 8;}
    //! Set the `systime` field
    void systime(uint32_t value) { raw &= ~(0x3fffull << 16); raw |= (uint64_t(value) & 0x3fff) << 16;}
    //! Set the `init_state` field
    void init_state(uint32_t value) { raw &= ~(0x3full << 30); raw |= (uint64_t(value) & 0x3f) << 30;}
    //! Set the `rx_data` field
    void rx_data(uint32_t value) { raw &= ~(0xffull << 36); raw |= (uint64_t(value) & 0xff) << 36;}
    //! Set the `tx_data` field
    void tx_data(uint32_t value) { raw &= ~(0xffull << 44); raw |= (uint64_t(value) & 0xff) << 44;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x800;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file SetHicannIfState at address 0x808.
struct SetHicannIfState
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    SetHicannIfState() = default;

    //! Initialize all fields with a specific value
    SetHicannIfState(uint32_t data_delay_, uint32_t data_delay_dout_)
    {
        raw |= (uint64_t(data_delay_) & 0x1f) << 0;
        raw |= (uint64_t(data_delay_dout_) & 0x1f) << 5;
    }
    
    //! Read the `data_delay` field
    uint32_t data_delay() const { return uint32_t(raw >> 0 & 0x1f);}
    //! Read the `data_delay_dout` field
    uint32_t data_delay_dout() const { return uint32_t(raw >> 5 & 0x1f);}

    
    //! Set the `data_delay` field
    void data_delay(uint32_t value) { raw &= ~(0x1full << 0); raw |= (uint64_t(value) & 0x1f) << 0;}
    //! Set the `data_delay_dout` field
    void data_delay_dout(uint32_t value) { raw &= ~(0x1full << 5); raw |= (uint64_t(value) & 0x1f) << 5;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x808;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file HicannIfRxConfig at address 0x810.
struct HicannIfRxConfig
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannIfRxConfig() = default;
    //! Initialize the single field with a specific value
    HicannIfRxConfig(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x810;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file HicannIfRxPulse at address 0x818.
struct HicannIfRxPulse
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannIfRxPulse() = default;

    //! Initialize all fields with a specific value
    HicannIfRxPulse(uint32_t data_)
    {
        raw |= (uint64_t(data_) & 0xffffff) << 0;
    }
    
    //! Read the `data` field
    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffff);}

    
    //! Set the `data` field
    void data(uint32_t value) { raw &= ~(0xffffffull << 0); raw |= (uint64_t(value) & 0xffffff) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x818;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-write register file HicannIfConfig at address 0x820.
struct HicannIfConfig
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannIfConfig() = default;

    //! Initialize all fields with a specific value
    HicannIfConfig(bool start_link_, bool loopback_enable_, bool auto_init_, bool init_master_, bool use_timestamp_, bool auto_limit_, bool pulse_protocol_, bool config_protocol_, uint32_t heap_mode_, uint32_t limit_, bool dc_coding_, bool invert_deserializer_data_)
    {
        raw |= (uint64_t(start_link_) & 0x1) << 0;
        raw |= (uint64_t(loopback_enable_) & 0x1) << 1;
        raw |= (uint64_t(auto_init_) & 0x1) << 2;
        raw |= (uint64_t(init_master_) & 0x1) << 3;
        raw |= (uint64_t(use_timestamp_) & 0x1) << 4;
        raw |= (uint64_t(auto_limit_) & 0x1) << 5;
        raw |= (uint64_t(pulse_protocol_) & 0x1) << 6;
        raw |= (uint64_t(config_protocol_) & 0x1) << 7;
        raw |= (uint64_t(heap_mode_) & 0xff) << 8;
        raw |= (uint64_t(limit_) & 0x7ff) << 16;
        raw |= (uint64_t(dc_coding_) & 0x1) << 27;
        raw |= (uint64_t(invert_deserializer_data_) & 0x1) << 28;
    }
    
    //! Read the `start_link` field
    bool start_link() const { return bool(raw >> 0 & 0x1);}
    //! Read the `loopback_enable` field
    bool loopback_enable() const { return bool(raw >> 1 & 0x1);}
    //! Read the `auto_init` field
    bool auto_init() const { return bool(raw >> 2 & 0x1);}
    //! Read the `init_master` field
    bool init_master() const { return bool(raw >> 3 & 0x1);}
    //! Read the `use_timestamp` field
    bool use_timestamp() const { return bool(raw >> 4 & 0x1);}
    //! Read the `auto_limit` field
    bool auto_limit() const { return bool(raw >> 5 & 0x1);}
    //! Read the `pulse_protocol` field
    bool pulse_protocol() const { return bool(raw >> 6 & 0x1);}
    //! Read the `config_protocol` field
    bool config_protocol() const { return bool(raw >> 7 & 0x1);}
    //! Read the `heap_mode` field
    uint32_t heap_mode() const { return uint32_t(raw >> 8 & 0xff);}
    //! Read the `limit` field
    uint32_t limit() const { return uint32_t(raw >> 16 & 0x7ff);}
    //! Read the `dc_coding` field
    bool dc_coding() const { return bool(raw >> 27 & 0x1);}
    //! Read the `invert_deserializer_data` field
    bool invert_deserializer_data() const { return bool(raw >> 28 & 0x1);}

    
    //! Set the `start_link` field
    void start_link(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    //! Set the `loopback_enable` field
    void loopback_enable(bool value) { raw &= ~(0x1ull << 1); raw |= (uint64_t(value) & 0x1) << 1;}
    //! Set the `auto_init` field
    void auto_init(bool value) { raw &= ~(0x1ull << 2); raw |= (uint64_t(value) & 0x1) << 2;}
    //! Set the `init_master` field
    void init_master(bool value) { raw &= ~(0x1ull << 3); raw |= (uint64_t(value) & 0x1) << 3;}
    //! Set the `use_timestamp` field
    void use_timestamp(bool value) { raw &= ~(0x1ull << 4); raw |= (uint64_t(value) & 0x1) << 4;}
    //! Set the `auto_limit` field
    void auto_limit(bool value) { raw &= ~(0x1ull << 5); raw |= (uint64_t(value) & 0x1) << 5;}
    //! Set the `pulse_protocol` field
    void pulse_protocol(bool value) { raw &= ~(0x1ull << 6); raw |= (uint64_t(value) & 0x1) << 6;}
    //! Set the `config_protocol` field
    void config_protocol(bool value) { raw &= ~(0x1ull << 7); raw |= (uint64_t(value) & 0x1) << 7;}
    //! Set the `heap_mode` field
    void heap_mode(uint32_t value) { raw &= ~(0xffull << 8); raw |= (uint64_t(value) & 0xff) << 8;}
    //! Set the `limit` field
    void limit(uint32_t value) { raw &= ~(0x7ffull << 16); raw |= (uint64_t(value) & 0x7ff) << 16;}
    //! Set the `dc_coding` field
    void dc_coding(bool value) { raw &= ~(0x1ull << 27); raw |= (uint64_t(value) & 0x1) << 27;}
    //! Set the `invert_deserializer_data` field
    void invert_deserializer_data(bool value) { raw &= ~(0x1ull << 28); raw |= (uint64_t(value) & 0x1) << 28;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x820;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Write-only register file HicannIfControls at address 0x828.
struct HicannIfControls
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannIfControls() = default;

    //! Initialize all fields with a specific value
    HicannIfControls(bool tx_hicann_pulse_enable_, bool tx_hicann_config_enable_, bool routing_data_enable_, bool channel_reset_, bool crc_count_reset_)
    {
        raw |= (uint64_t(tx_hicann_pulse_enable_) & 0x1) << 0;
        raw |= (uint64_t(tx_hicann_config_enable_) & 0x1) << 1;
        raw |= (uint64_t(routing_data_enable_) & 0x1) << 2;
        raw |= (uint64_t(channel_reset_) & 0x1) << 3;
        raw |= (uint64_t(crc_count_reset_) & 0x1) << 4;
    }
    
    //! Read the `tx_hicann_pulse_enable` field
    bool tx_hicann_pulse_enable() const { return bool(raw >> 0 & 0x1);}
    //! Read the `tx_hicann_config_enable` field
    bool tx_hicann_config_enable() const { return bool(raw >> 1 & 0x1);}
    //! Read the `routing_data_enable` field
    bool routing_data_enable() const { return bool(raw >> 2 & 0x1);}
    //! Read the `channel_reset` field
    bool channel_reset() const { return bool(raw >> 3 & 0x1);}
    //! Read the `crc_count_reset` field
    bool crc_count_reset() const { return bool(raw >> 4 & 0x1);}

    
    //! Set the `tx_hicann_pulse_enable` field
    void tx_hicann_pulse_enable(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    //! Set the `tx_hicann_config_enable` field
    void tx_hicann_config_enable(bool value) { raw &= ~(0x1ull << 1); raw |= (uint64_t(value) & 0x1) << 1;}
    //! Set the `routing_data_enable` field
    void routing_data_enable(bool value) { raw &= ~(0x1ull << 2); raw |= (uint64_t(value) & 0x1) << 2;}
    //! Set the `channel_reset` field
    void channel_reset(bool value) { raw &= ~(0x1ull << 3); raw |= (uint64_t(value) & 0x1) << 3;}
    //! Set the `crc_count_reset` field
    void crc_count_reset(bool value) { raw &= ~(0x1ull << 4); raw |= (uint64_t(value) & 0x1) << 4;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x828;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HicannIfTxData at address 0x830.
//! This register can be used to emulate highspeed packets via Jtag
struct HicannIfTxData
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannIfTxData() = default;
    //! Initialize the single field with a specific value
    HicannIfTxData(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x830;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HicannIfNeuronAddressFilter at address 0x838.
struct HicannIfNeuronAddressFilter
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannIfNeuronAddressFilter() = default;

    //! Initialize all fields with a specific value
    HicannIfNeuronAddressFilter(uint32_t negative_filter_mask_, uint32_t positive_filter_mask_)
    {
        raw |= (uint64_t(negative_filter_mask_) & 0x1ff) << 0;
        raw |= (uint64_t(positive_filter_mask_) & 0x1ff) << 9;
    }
    
    //! Read the `negative_filter_mask` field
    uint32_t negative_filter_mask() const { return uint32_t(raw >> 0 & 0x1ff);}
    //! Read the `positive_filter_mask` field
    uint32_t positive_filter_mask() const { return uint32_t(raw >> 9 & 0x1ff);}

    
    //! Set the `negative_filter_mask` field
    void negative_filter_mask(uint32_t value) { raw &= ~(0x1ffull << 0); raw |= (uint64_t(value) & 0x1ff) << 0;}
    //! Set the `positive_filter_mask` field
    void positive_filter_mask(uint32_t value) { raw &= ~(0x1ffull << 9); raw |= (uint64_t(value) & 0x1ff) << 9;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x838;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HicannPacketGen at address 0x840.
struct HicannPacketGen
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannPacketGen() = default;

    //! Initialize all fields with a specific value
    HicannPacketGen(uint32_t count_, bool error_, bool enable_)
    {
        raw |= (uint64_t(count_) & 0x1ffffff) << 0;
        raw |= (uint64_t(error_) & 0x1) << 25;
        raw |= (uint64_t(enable_) & 0x1) << 26;
    }
    
    //! Read the `count` field
    uint32_t count() const { return uint32_t(raw >> 0 & 0x1ffffff);}
    //! Read the `error` field
    bool error() const { return bool(raw >> 25 & 0x1);}
    //! Read the `enable` field
    bool enable() const { return bool(raw >> 26 & 0x1);}

    
    //! Set the `count` field
    void count(uint32_t value) { raw &= ~(0x1ffffffull << 0); raw |= (uint64_t(value) & 0x1ffffff) << 0;}
    //! Set the `error` field
    void error(bool value) { raw &= ~(0x1ull << 25); raw |= (uint64_t(value) & 0x1) << 25;}
    //! Set the `enable` field
    void enable(bool value) { raw &= ~(0x1ull << 26); raw |= (uint64_t(value) & 0x1) << 26;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x840;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HicannChannel at address 0x848.
//! This register selects the Hicann the Fpga will communicate with. Note, that
//! the DNC order is expected here and not the Jtag order.
struct HicannChannel
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannChannel() = default;

    //! Initialize all fields with a specific value
    HicannChannel(uint32_t number_)
    {
        raw |= (uint64_t(number_) & 0x7) << 0;
    }
    
    //! Read the `number` field
    uint32_t number() const { return uint32_t(raw >> 0 & 0x7);}

    
    //! Set the `number` field
    void number(uint32_t value) { raw &= ~(0x7ull << 0); raw |= (uint64_t(value) & 0x7) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x848;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HicannTxIfPower at address 0x868.
struct HicannTxIfPower
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannTxIfPower() = default;

    //! Initialize all fields with a specific value
    HicannTxIfPower(uint32_t channel0_, uint32_t channel1_, uint32_t channel2_, uint32_t channel3_, uint32_t channel4_, uint32_t channel5_, uint32_t channel6_, uint32_t channel7_)
    {
        raw |= (uint64_t(channel0_) & 0x3) << 0;
        raw |= (uint64_t(channel1_) & 0x3) << 2;
        raw |= (uint64_t(channel2_) & 0x3) << 4;
        raw |= (uint64_t(channel3_) & 0x3) << 6;
        raw |= (uint64_t(channel4_) & 0x3) << 8;
        raw |= (uint64_t(channel5_) & 0x3) << 10;
        raw |= (uint64_t(channel6_) & 0x3) << 12;
        raw |= (uint64_t(channel7_) & 0x3) << 14;
    }
    
    //! Read the `channel0` field
    uint32_t channel0() const { return uint32_t(raw >> 0 & 0x3);}
    //! Read the `channel1` field
    uint32_t channel1() const { return uint32_t(raw >> 2 & 0x3);}
    //! Read the `channel2` field
    uint32_t channel2() const { return uint32_t(raw >> 4 & 0x3);}
    //! Read the `channel3` field
    uint32_t channel3() const { return uint32_t(raw >> 6 & 0x3);}
    //! Read the `channel4` field
    uint32_t channel4() const { return uint32_t(raw >> 8 & 0x3);}
    //! Read the `channel5` field
    uint32_t channel5() const { return uint32_t(raw >> 10 & 0x3);}
    //! Read the `channel6` field
    uint32_t channel6() const { return uint32_t(raw >> 12 & 0x3);}
    //! Read the `channel7` field
    uint32_t channel7() const { return uint32_t(raw >> 14 & 0x3);}

    
    //! Set the `channel0` field
    void channel0(uint32_t value) { raw &= ~(0x3ull << 0); raw |= (uint64_t(value) & 0x3) << 0;}
    //! Set the `channel1` field
    void channel1(uint32_t value) { raw &= ~(0x3ull << 2); raw |= (uint64_t(value) & 0x3) << 2;}
    //! Set the `channel2` field
    void channel2(uint32_t value) { raw &= ~(0x3ull << 4); raw |= (uint64_t(value) & 0x3) << 4;}
    //! Set the `channel3` field
    void channel3(uint32_t value) { raw &= ~(0x3ull << 6); raw |= (uint64_t(value) & 0x3) << 6;}
    //! Set the `channel4` field
    void channel4(uint32_t value) { raw &= ~(0x3ull << 8); raw |= (uint64_t(value) & 0x3) << 8;}
    //! Set the `channel5` field
    void channel5(uint32_t value) { raw &= ~(0x3ull << 10); raw |= (uint64_t(value) & 0x3) << 10;}
    //! Set the `channel6` field
    void channel6(uint32_t value) { raw &= ~(0x3ull << 12); raw |= (uint64_t(value) & 0x3) << 12;}
    //! Set the `channel7` field
    void channel7(uint32_t value) { raw &= ~(0x3ull << 14); raw |= (uint64_t(value) & 0x3) << 14;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x868;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file TestControlMode at address 0xc00.
//! This enabled the application layer test mode
struct TestControlMode
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TestControlMode() = default;

    //! Initialize all fields with a specific value
    TestControlMode(uint32_t mode_)
    {
        raw |= (uint64_t(mode_) & 0x3) << 0;
    }
    
    //! Read the `mode` field
    uint32_t mode() const { return uint32_t(raw >> 0 & 0x3);}

    
    //! Set the `mode` field
    void mode(uint32_t value) { raw &= ~(0x3ull << 0); raw |= (uint64_t(value) & 0x3) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc00;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file TestControlConfig at address 0xc08.
//! This configures an application layer test run. The number of quad words to send,
//! the number of clock cycles to wait between each packet and whether to count
//! up the value in the payload can be specified here.
struct TestControlConfig
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TestControlConfig() = default;

    //! Initialize all fields with a specific value
    TestControlConfig(uint32_t quad_words_, uint32_t pause_time_, bool count_up_)
    {
        raw |= (uint64_t(quad_words_) & 0xff) << 0;
        raw |= (uint64_t(pause_time_) & 0xff) << 8;
        raw |= (uint64_t(count_up_) & 0x1) << 16;
    }
    
    //! Read the `quad_words` field
    uint32_t quad_words() const { return uint32_t(raw >> 0 & 0xff);}
    //! Read the `pause_time` field
    uint32_t pause_time() const { return uint32_t(raw >> 8 & 0xff);}
    //! Read the `count_up` field
    bool count_up() const { return bool(raw >> 16 & 0x1);}

    
    //! Set the `quad_words` field
    void quad_words(uint32_t value) { raw &= ~(0xffull << 0); raw |= (uint64_t(value) & 0xff) << 0;}
    //! Set the `pause_time` field
    void pause_time(uint32_t value) { raw &= ~(0xffull << 8); raw |= (uint64_t(value) & 0xff) << 8;}
    //! Set the `count_up` field
    void count_up(bool value) { raw &= ~(0x1ull << 16); raw |= (uint64_t(value) & 0x1) << 16;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc08;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file TestControlStart at address 0xc10.
//! This starts an application layer test run.
//! 
//! Writing a `1` will start the test. When the test is done, the hardware will
//! reset the bit to zero.
struct TestControlStart
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TestControlStart() = default;

    //! Initialize all fields with a specific value
    TestControlStart(bool start_)
    {
        raw |= (uint64_t(start_) & 0x1) << 0;
    }
    
    //! Read the `start` field
    bool start() const { return bool(raw >> 0 & 0x1);}

    
    //! Set the `start` field
    void start(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc10;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file TestControlData at address 0xc18.
//! The payload data that is send during the test runs.
//! 
//! Use the count_up from the TestControlConfig to automatically increment it
//! after each packet.
struct TestControlData
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TestControlData() = default;
    //! Initialize the single field with a specific value
    TestControlData(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc18;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file TestControlType at address 0xc20.
//! The payload type that is send during the test runs.
//! 
//! These will be included in the notification class field.
struct TestControlType
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;
    //! All possible values for the `type` field.
    enum class Type : uint16_t
    {
        TracePulse = 3237,
        FpgaConfig = 3099,
        HicannConfig = 10779,
    };
    //! Convenience alias for the `Type` enum
    constexpr static Type TracePulse = Type::TracePulse;
    //! Convenience alias for the `Type` enum
    constexpr static Type FpgaConfig = Type::FpgaConfig;
    //! Convenience alias for the `Type` enum
    constexpr static Type HicannConfig = Type::HicannConfig;

    //! Initialize all fields with zero
    TestControlType() = default;

    //! Initialize all fields with a specific value
    TestControlType(Type type_)
    {
        raw |= (uint64_t(type_) & 0xffff) << 0;
    }
    
    //! Read the `type` field
    Type type() const { return Type(raw >> 0 & 0xffff);}

    
    //! Set the `type` field
    void type(Type value) { raw &= ~(0xffffull << 0); raw |= (uint64_t(value) & 0xffff) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc20;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Write-only register file AlTestCounterReset at address 0xc28.
struct AlTestCounterReset
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlTestCounterReset() = default;

    //! Initialize all fields with a specific value
    AlTestCounterReset(bool reset_)
    {
        raw |= (uint64_t(reset_) & 0x1) << 0;
    }
    
    //! Read the `reset` field
    bool reset() const { return bool(raw >> 0 & 0x1);}

    
    //! Set the `reset` field
    void reset(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc28;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file AlHicannConfigReceived at address 0xc30.
struct AlHicannConfigReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlHicannConfigReceived() = default;
    //! Initialize the single field with a specific value
    AlHicannConfigReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc30;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file AlFpgaConfigReceived at address 0xc38.
struct AlFpgaConfigReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlFpgaConfigReceived() = default;
    //! Initialize the single field with a specific value
    AlFpgaConfigReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc38;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file AlPlaybackDataReceived at address 0xc40.
struct AlPlaybackDataReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlPlaybackDataReceived() = default;
    //! Initialize the single field with a specific value
    AlPlaybackDataReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc40;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file AlJtagReceived at address 0xc48.
struct AlJtagReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlJtagReceived() = default;
    //! Initialize the single field with a specific value
    AlJtagReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc48;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file AlErrorUnknownTypeReceived at address 0xc50.
struct AlErrorUnknownTypeReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlErrorUnknownTypeReceived() = default;
    //! Initialize the single field with a specific value
    AlErrorUnknownTypeReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc50;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file AlHicannConfigSent at address 0xc58.
struct AlHicannConfigSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlHicannConfigSent() = default;
    //! Initialize the single field with a specific value
    AlHicannConfigSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc58;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file AlFpgaConfigSent at address 0xc60.
struct AlFpgaConfigSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlFpgaConfigSent() = default;
    //! Initialize the single field with a specific value
    AlFpgaConfigSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc60;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file AlTracePulseSent at address 0xc68.
struct AlTracePulseSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlTracePulseSent() = default;
    //! Initialize the single field with a specific value
    AlTracePulseSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc68;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file AlJtagSent at address 0xc70.
struct AlJtagSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlJtagSent() = default;
    //! Initialize the single field with a specific value
    AlJtagSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc70;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file AlErrorUnknownTypeSent at address 0xc78.
struct AlErrorUnknownTypeSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    AlErrorUnknownTypeSent() = default;
    //! Initialize the single field with a specific value
    AlErrorUnknownTypeSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0xc78;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-write register file TraceBufferStart at address 0x1000.
//! Address in bytes of the start of the trace-pulse data ringbuffer.
//! 
//! This can be a physical or a logical address. For a logical address
//! the HostEndpoint node must be set to `0x4`.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct TraceBufferStart
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceBufferStart() = default;
    //! Initialize the single field with a specific value
    TraceBufferStart(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1000;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file TraceBufferSize at address 0x1008.
//! The capacity of the trace-pulse data ringbuffer in bytes.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct TraceBufferSize
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceBufferSize() = default;

    //! Initialize all fields with a specific value
    TraceBufferSize(uint32_t data_)
    {
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }
    
    //! Read the `data` field
    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}

    
    //! Set the `data` field
    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1008;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file TraceBufferFullThreshold at address 0x1010.
//! The threshold that determines the full state of the trace-pulse data ringbuffer.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct TraceBufferFullThreshold
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceBufferFullThreshold() = default;

    //! Initialize all fields with a specific value
    TraceBufferFullThreshold(uint32_t data_)
    {
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }
    
    //! Read the `data` field
    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}

    
    //! Set the `data` field
    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1010;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file TraceBufferCounter at address 0x1018.
//! Various counters that report the number of successful initializations of the
//! trace-pulse data ringbuffer and the number of wrap arounds of the buffer.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct TraceBufferCounter
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceBufferCounter() = default;

    //! Initialize all fields with a specific value
    TraceBufferCounter(uint32_t start_address_, uint32_t size_, uint32_t threshold_, uint32_t wraps_)
    {
        raw |= (uint64_t(start_address_) & 0xffff) << 0;
        raw |= (uint64_t(size_) & 0xffff) << 16;
        raw |= (uint64_t(threshold_) & 0xffff) << 32;
        raw |= (uint64_t(wraps_) & 0xffff) << 48;
    }
    
    //! Read the `start_address` field
    uint32_t start_address() const { return uint32_t(raw >> 0 & 0xffff);}
    //! Read the `size` field
    uint32_t size() const { return uint32_t(raw >> 16 & 0xffff);}
    //! Read the `threshold` field
    uint32_t threshold() const { return uint32_t(raw >> 32 & 0xffff);}
    //! Read the `wraps` field
    uint32_t wraps() const { return uint32_t(raw >> 48 & 0xffff);}

    
    //! Set the `start_address` field
    void start_address(uint32_t value) { raw &= ~(0xffffull << 0); raw |= (uint64_t(value) & 0xffff) << 0;}
    //! Set the `size` field
    void size(uint32_t value) { raw &= ~(0xffffull << 16); raw |= (uint64_t(value) & 0xffff) << 16;}
    //! Set the `threshold` field
    void threshold(uint32_t value) { raw &= ~(0xffffull << 32); raw |= (uint64_t(value) & 0xffff) << 32;}
    //! Set the `wraps` field
    void wraps(uint32_t value) { raw &= ~(0xffffull << 48); raw |= (uint64_t(value) & 0xffff) << 48;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1018;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Write-only register file TraceBufferCounterReset at address 0x1020.
//! Writing a `1` will reset the start_address, size and threshold of TraceBufferCounter.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct TraceBufferCounterReset
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceBufferCounterReset() = default;

    //! Initialize all fields with a specific value
    TraceBufferCounterReset(bool reset_)
    {
        raw |= (uint64_t(reset_) & 0x1) << 0;
    }
    
    //! Read the `reset` field
    bool reset() const { return bool(raw >> 0 & 0x1);}

    
    //! Set the `reset` field
    void reset(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1020;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file TraceBufferCurrentAddress at address 0x1028.
//! The address the hardware will send the next packet to.
struct TraceBufferCurrentAddress
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceBufferCurrentAddress() = default;
    //! Initialize the single field with a specific value
    TraceBufferCurrentAddress(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1028;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file TraceBufferEndAddress at address 0x1030.
//! The calculated end address of the trace-pulse data ringbuffer.
struct TraceBufferEndAddress
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceBufferEndAddress() = default;
    //! Initialize the single field with a specific value
    TraceBufferEndAddress(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1030;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file TraceBufferFreeSpace at address 0x1038.
//! The amount of free space inside the trace-pulse data ringbuffer in quad words.
struct TraceBufferFreeSpace
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceBufferFreeSpace() = default;

    //! Initialize all fields with a specific value
    TraceBufferFreeSpace(uint32_t data_)
    {
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }
    
    //! Read the `data` field
    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}

    
    //! Set the `data` field
    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1038;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-write register file TraceBufferInit at address 0x1040.
//! Writing a `1` will reconfigure the trace-pulse data ringbuffer according to
//! the previously written config values.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct TraceBufferInit
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceBufferInit() = default;

    //! Initialize all fields with a specific value
    TraceBufferInit(bool start_)
    {
        raw |= (uint64_t(start_) & 0x1) << 0;
    }
    
    //! Read the `start` field
    bool start() const { return bool(raw >> 0 & 0x1);}

    
    //! Set the `start` field
    void start(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1040;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HicannBufferStart at address 0x1080.
//! Address in bytes of the start of the hicann config data ringbuffer.
//! 
//! This can be a physical or a logical address. For a logical address
//! the HostEndpoint node must be set to `0x4`.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct HicannBufferStart
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannBufferStart() = default;
    //! Initialize the single field with a specific value
    HicannBufferStart(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1080;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HicannBufferSize at address 0x1088.
//! The capacity of the hicann config data ringbuffer in bytes.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct HicannBufferSize
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannBufferSize() = default;

    //! Initialize all fields with a specific value
    HicannBufferSize(uint32_t data_)
    {
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }
    
    //! Read the `data` field
    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}

    
    //! Set the `data` field
    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1088;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HicannBufferFullThreshold at address 0x1090.
//! The threshold that determines the full state of the hicann config data ringbuffer.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct HicannBufferFullThreshold
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannBufferFullThreshold() = default;

    //! Initialize all fields with a specific value
    HicannBufferFullThreshold(uint32_t data_)
    {
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }
    
    //! Read the `data` field
    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}

    
    //! Set the `data` field
    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1090;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file HicannBufferCounter at address 0x1098.
//! Various counters that report the number of successful initializations of the
//! hicann config data ringbuffer and the number of wrap arounds of the buffer.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct HicannBufferCounter
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannBufferCounter() = default;

    //! Initialize all fields with a specific value
    HicannBufferCounter(uint32_t start_address_, uint32_t size_, uint32_t threshold_, uint32_t wraps_)
    {
        raw |= (uint64_t(start_address_) & 0xffff) << 0;
        raw |= (uint64_t(size_) & 0xffff) << 16;
        raw |= (uint64_t(threshold_) & 0xffff) << 32;
        raw |= (uint64_t(wraps_) & 0xffff) << 48;
    }
    
    //! Read the `start_address` field
    uint32_t start_address() const { return uint32_t(raw >> 0 & 0xffff);}
    //! Read the `size` field
    uint32_t size() const { return uint32_t(raw >> 16 & 0xffff);}
    //! Read the `threshold` field
    uint32_t threshold() const { return uint32_t(raw >> 32 & 0xffff);}
    //! Read the `wraps` field
    uint32_t wraps() const { return uint32_t(raw >> 48 & 0xffff);}

    
    //! Set the `start_address` field
    void start_address(uint32_t value) { raw &= ~(0xffffull << 0); raw |= (uint64_t(value) & 0xffff) << 0;}
    //! Set the `size` field
    void size(uint32_t value) { raw &= ~(0xffffull << 16); raw |= (uint64_t(value) & 0xffff) << 16;}
    //! Set the `threshold` field
    void threshold(uint32_t value) { raw &= ~(0xffffull << 32); raw |= (uint64_t(value) & 0xffff) << 32;}
    //! Set the `wraps` field
    void wraps(uint32_t value) { raw &= ~(0xffffull << 48); raw |= (uint64_t(value) & 0xffff) << 48;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1098;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Write-only register file HicannBufferCounterReset at address 0x10a0.
//! Writing a `1` will reset the start_address, size and threshold of TraceBufferCounter.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct HicannBufferCounterReset
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannBufferCounterReset() = default;

    //! Initialize all fields with a specific value
    HicannBufferCounterReset(bool reset_)
    {
        raw |= (uint64_t(reset_) & 0x1) << 0;
    }
    
    //! Read the `reset` field
    bool reset() const { return bool(raw >> 0 & 0x1);}

    
    //! Set the `reset` field
    void reset(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x10a0;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file HicannBufferCurrentAddress at address 0x10a8.
//! The address the hardware will send the next packet to.
struct HicannBufferCurrentAddress
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannBufferCurrentAddress() = default;
    //! Initialize the single field with a specific value
    HicannBufferCurrentAddress(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x10a8;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file HicannBufferEndAddress at address 0x10b0.
//! The calculated end address of the hicann config data ringbuffer.
struct HicannBufferEndAddress
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannBufferEndAddress() = default;
    //! Initialize the single field with a specific value
    HicannBufferEndAddress(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t data() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void data(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x10b0;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file HicannBufferFreeSpace at address 0x10b8.
//! The amount of free space inside the hicann config data ringbuffer in quad words.
struct HicannBufferFreeSpace
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannBufferFreeSpace() = default;

    //! Initialize all fields with a specific value
    HicannBufferFreeSpace(uint32_t data_)
    {
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }
    
    //! Read the `data` field
    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}

    
    //! Set the `data` field
    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x10b8;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-write register file HicannBufferInit at address 0x10c0.
//! Writing a `1` will reconfigure the hicann config data ringbuffer according to
//! the previously written config values.
//! 
//! For a high-level interface use the Fpga::configure_partner_host method.
struct HicannBufferInit
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannBufferInit() = default;

    //! Initialize all fields with a specific value
    HicannBufferInit(bool start_)
    {
        raw |= (uint64_t(start_) & 0x1) << 0;
    }
    
    //! Read the `start` field
    bool start() const { return bool(raw >> 0 & 0x1);}

    
    //! Set the `start` field
    void start(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x10c0;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file RraPutReceived at address 0x1100.
//! Counts the number or register file write commands received
struct RraPutReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    RraPutReceived() = default;
    //! Initialize the single field with a specific value
    RraPutReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1100;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file RraGetReceived at address 0x1108.
//! Counts the number of register file read commands received
struct RraGetReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    RraGetReceived() = default;
    //! Initialize the single field with a specific value
    RraGetReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1108;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file RmaPutReceived at address 0x1110.
//! Counts the number of remote memory access commands received
struct RmaPutReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    RmaPutReceived() = default;
    //! Initialize the single field with a specific value
    RmaPutReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1110;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file RmaNotificationReceived at address 0x1118.
//! Counts the number of remote memory access notifications received
struct RmaNotificationReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    RmaNotificationReceived() = default;
    //! Initialize the single field with a specific value
    RmaNotificationReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1118;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file PlaybackReceived at address 0x1120.
//! Counts the number of received playback data packets
struct PlaybackReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    PlaybackReceived() = default;
    //! Initialize the single field with a specific value
    PlaybackReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1120;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file FpgaConfigReceived at address 0x1128.
//! Counts the number of Fpga config packets received.
struct FpgaConfigReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    FpgaConfigReceived() = default;
    //! Initialize the single field with a specific value
    FpgaConfigReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1128;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file HicannConfigReceived at address 0x1130.
//! Counts the number of Hicann config packets received.
struct HicannConfigReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannConfigReceived() = default;
    //! Initialize the single field with a specific value
    HicannConfigReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1130;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file JtagDataReceived at address 0x1138.
//! Counts the number of Jtag packets received.
struct JtagDataReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    JtagDataReceived() = default;
    //! Initialize the single field with a specific value
    JtagDataReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1138;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file NeighbourDataReceived at address 0x1140.
//! Counts the number of pulse routing packets from neighboring Fpgas.
struct NeighbourDataReceived
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    NeighbourDataReceived() = default;
    //! Initialize the single field with a specific value
    NeighbourDataReceived(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1140;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Write-only register file CounterReset at address 0x1148.
//! Resets the following performance counters:
//! - RraPutReceived
//! - RraGetReceived
//! - RmaPutReceived
//! - RmaNotificationReceived
//! - PlaybackReceived
//! - FpgaConfigReceived
//! - HicannConfigReceived
//! - JtagDataReceived
//! - NeighbourDataReceived
//! 
//! And the following error counters:
//! - InvalidCommand
//! - InvalidType
//! - InvalidPayloadSize
//! - InvalidFields
//! - InvalidMode
//! - InvalidRraAddress
//! - InvalidHost
struct CounterReset
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    CounterReset() = default;

    //! Initialize all fields with a specific value
    CounterReset(bool reset_)
    {
        raw |= (uint64_t(reset_) & 0x1) << 0;
    }
    
    //! Read the `reset` field
    bool reset() const { return bool(raw >> 0 & 0x1);}

    
    //! Set the `reset` field
    void reset(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1148;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file InvalidCommand at address 0x1150.
//! Number of invalid commands received on Rma requests in completer.
struct InvalidCommand
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    InvalidCommand() = default;
    //! Initialize the single field with a specific value
    InvalidCommand(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1150;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file InvalidType at address 0x1158.
//! Number of invalid payload-types received on Rma requests in completer.
struct InvalidType
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    InvalidType() = default;
    //! Initialize the single field with a specific value
    InvalidType(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1158;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file InvalidPayloadSize at address 0x1160.
//! Number of invalid payload-sizes received on Rma requests in completer.
struct InvalidPayloadSize
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    InvalidPayloadSize() = default;
    //! Initialize the single field with a specific value
    InvalidPayloadSize(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1160;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file InvalidFields at address 0x1168.
//! Number of received Rma requests with marked error-fields in completer.
struct InvalidFields
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    InvalidFields() = default;
    //! Initialize the single field with a specific value
    InvalidFields(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1168;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file InvalidMode at address 0x1170.
//! Number of received Rma requests with error in mode-fields in completer.
struct InvalidMode
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    InvalidMode() = default;
    //! Initialize the single field with a specific value
    InvalidMode(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1170;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file InvalidRraAddress at address 0x1208.
//! Number of invalid Rra-addresses received.
struct InvalidRraAddress
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    InvalidRraAddress() = default;
    //! Initialize the single field with a specific value
    InvalidRraAddress(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1208;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file ConfigAddressReinit at address 0x1210.
//! Number of attempts to reinit the host-addresses for fpga-config answers.
//! 
//! Note: this is an error in the original register file documentation, but should
//! actually be considered as a normal counter.
struct ConfigAddressReinit
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    ConfigAddressReinit() = default;
    //! Initialize the single field with a specific value
    ConfigAddressReinit(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1210;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file UndefinedHost at address 0x1180.
//! Number of attempts to send data to an unconfigured host.
struct UndefinedHost
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    UndefinedHost() = default;
    //! Initialize the single field with a specific value
    UndefinedHost(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1180;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file RraGetResponsesSent at address 0x1188.
//! Number of RRA-get-responses sent in responder.
struct RraGetResponsesSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    RraGetResponsesSent() = default;
    //! Initialize the single field with a specific value
    RraGetResponsesSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1188;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file RmaPutRequestsSent at address 0x1190.
//! Number of RMA-put-requests sent in responder.
struct RmaPutRequestsSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    RmaPutRequestsSent() = default;
    //! Initialize the single field with a specific value
    RmaPutRequestsSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1190;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file ReceiptNotificationPutRequestsSent at address 0x1198.
//! Number of RMA-notification-put-requests sent in responder
struct ReceiptNotificationPutRequestsSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    ReceiptNotificationPutRequestsSent() = default;
    //! Initialize the single field with a specific value
    ReceiptNotificationPutRequestsSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1198;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file PayloadNotificationPutRequestsSent at address 0x11a0.
//! ...
struct PayloadNotificationPutRequestsSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    PayloadNotificationPutRequestsSent() = default;
    //! Initialize the single field with a specific value
    PayloadNotificationPutRequestsSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x11a0;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file TraceDataSent at address 0x11a8.
//! Number of Trace-Pulse-Data packets sent in responder.
struct TraceDataSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceDataSent() = default;
    //! Initialize the single field with a specific value
    TraceDataSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x11a8;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file FpagConfigSent at address 0x11b0.
//! Number of Fpga-Configuration packets sent in responder.
struct FpagConfigSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    FpagConfigSent() = default;
    //! Initialize the single field with a specific value
    FpagConfigSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x11b0;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file HicannConfigSent at address 0x11b8.
//! Number of Hicann-Configuration answer packets sent in responder.
struct HicannConfigSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannConfigSent() = default;
    //! Initialize the single field with a specific value
    HicannConfigSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x11b8;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file JtagDataSent at address 0x11c0.
//! Number of Jtag-data packets sent in responder.
struct JtagDataSent
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    JtagDataSent() = default;
    //! Initialize the single field with a specific value
    JtagDataSent(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x11c0;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file NeighbourPulseSend at address 0x11c8.
//! Number of Neighbour-Pulse-data packets sent in responder.
struct NeighbourPulseSend
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    NeighbourPulseSend() = default;
    //! Initialize the single field with a specific value
    NeighbourPulseSend(uint64_t value)
    : raw(value & 0xffffffffffff) {}

    //! Read the single field
    uint64_t count() const { return raw & 0xffffffffffff;};
    //! Set the single field
    void count(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x11c8;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Write-only register file ResponderCounterReset at address 0x11d0.
//! Reset performance and error counters.
struct ResponderCounterReset
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    ResponderCounterReset() = default;

    //! Initialize all fields with a specific value
    ResponderCounterReset(bool reset_, uint64_t count_)
    {
        raw |= (uint64_t(reset_) & 0x1) << 0;
        raw |= (uint64_t(count_) & 0xffffffffffff) << 1;
    }
    
    //! Read the `reset` field
    bool reset() const { return bool(raw >> 0 & 0x1);}
    //! Read the `count` field
    uint64_t count() const { return uint64_t(raw >> 1 & 0xffffffffffff);}

    
    //! Set the `reset` field
    void reset(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    //! Set the `count` field
    void count(uint64_t value) { raw &= ~(0xffffffffffffull << 1); raw |= (uint64_t(value) & 0xffffffffffff) << 1;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x11d0;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Write-only register file NhtlCounterReset at address 0x1200.
struct NhtlCounterReset
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    NhtlCounterReset() = default;

    //! Initialize all fields with a specific value
    NhtlCounterReset(bool reset_)
    {
        raw |= (uint64_t(reset_) & 0x1) << 0;
    }
    
    //! Read the `reset` field
    bool reset() const { return bool(raw >> 0 & 0x1);}

    
    //! Set the `reset` field
    void reset(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1200;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = false;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HostEndpoint at address 0x1218.
//! Configures the Fpga with data from the local node.
//! 
//! The node id, protection domain and virtual process id all refer to the
//! local host node. Mode must be set to `0x4` when any address is a logical
//! address. It must be set to `0x0` when any address is a physical address.
//! Therefor, it is not possible to mix logical and physical addresses.
//! 
//! The addresses in question are:
//! - TraceBufferStart
//! - HicannBufferStart
//! - ConfigResponse
struct HostEndpoint
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HostEndpoint() = default;

    //! Initialize all fields with a specific value
    HostEndpoint(uint32_t node_id_, uint32_t protection_domain_, uint32_t vpid_, uint32_t mode_)
    {
        raw |= (uint64_t(node_id_) & 0xffff) << 0;
        raw |= (uint64_t(protection_domain_) & 0xffff) << 16;
        raw |= (uint64_t(vpid_) & 0x3ff) << 32;
        raw |= (uint64_t(mode_) & 0x3f) << 42;
    }
    
    //! Read the `node_id` field
    uint32_t node_id() const { return uint32_t(raw >> 0 & 0xffff);}
    //! Read the `protection_domain` field
    uint32_t protection_domain() const { return uint32_t(raw >> 16 & 0xffff);}
    //! Read the `vpid` field
    uint32_t vpid() const { return uint32_t(raw >> 32 & 0x3ff);}
    //! Read the `mode` field
    uint32_t mode() const { return uint32_t(raw >> 42 & 0x3f);}

    
    //! Set the `node_id` field
    void node_id(uint32_t value) { raw &= ~(0xffffull << 0); raw |= (uint64_t(value) & 0xffff) << 0;}
    //! Set the `protection_domain` field
    void protection_domain(uint32_t value) { raw &= ~(0xffffull << 16); raw |= (uint64_t(value) & 0xffff) << 16;}
    //! Set the `vpid` field
    void vpid(uint32_t value) { raw &= ~(0x3ffull << 32); raw |= (uint64_t(value) & 0x3ff) << 32;}
    //! Set the `mode` field
    void mode(uint32_t value) { raw &= ~(0x3full << 42); raw |= (uint64_t(value) & 0x3f) << 42;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1218;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file ConfigResponse at address 0x1220.
//! Address of the Fpga config response packets.
//! 
//! This can be a physical or a logical address. For a logical address
//! the HostEndpoint node must be set to `0x4`.
struct ConfigResponse
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    ConfigResponse() = default;
    //! Initialize the single field with a specific value
    ConfigResponse(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t address() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void address(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1220;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file TraceNotificationBehaviour at address 0x1228.
//! The notification behavior of the trace-pulse data ringbuffer.
//! 
//! Frequency is the number of packets after which the Fpga will send a payload
//! notification to the host. Timeout specifies the number of clock cycles after
//! which the Fpga will send a notification in case the number of packets is lower
//! than the frequency.
struct TraceNotificationBehaviour
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    TraceNotificationBehaviour() = default;

    //! Initialize all fields with a specific value
    TraceNotificationBehaviour(uint32_t timeout_, uint32_t frequency_)
    {
        raw |= (uint64_t(timeout_) & 0xffffffff) << 0;
        raw |= (uint64_t(frequency_) & 0xffffffff) << 32;
    }
    
    //! Read the `timeout` field
    uint32_t timeout() const { return uint32_t(raw >> 0 & 0xffffffff);}
    //! Read the `frequency` field
    uint32_t frequency() const { return uint32_t(raw >> 32 & 0xffffffff);}

    
    //! Set the `timeout` field
    void timeout(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    //! Set the `frequency` field
    void frequency(uint32_t value) { raw &= ~(0xffffffffull << 32); raw |= (uint64_t(value) & 0xffffffff) << 32;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1228;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-write register file HicannNotificationBehaviour at address 0x1230.
//! The notification behavior of the hicann config ringbuffer.
//! 
//! Frequency is the number of packets after which the Fpga will send a payload
//! notification to the host. Timeout specifies the number of clock cycles after
//! which the Fpga will send a notification in case the number of packets is lower
//! than the frequency.
struct HicannNotificationBehaviour
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    HicannNotificationBehaviour() = default;

    //! Initialize all fields with a specific value
    HicannNotificationBehaviour(uint32_t timeout_, uint32_t frequency_)
    {
        raw |= (uint64_t(timeout_) & 0xffffffff) << 0;
        raw |= (uint64_t(frequency_) & 0xffffffff) << 32;
    }
    
    //! Read the `timeout` field
    uint32_t timeout() const { return uint32_t(raw >> 0 & 0xffffffff);}
    //! Read the `frequency` field
    uint32_t frequency() const { return uint32_t(raw >> 32 & 0xffffffff);}

    
    //! Set the `timeout` field
    void timeout(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    //! Set the `frequency` field
    void frequency(uint32_t value) { raw &= ~(0xffffffffull << 32); raw |= (uint64_t(value) & 0xffffffff) << 32;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x1230;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = true;
};


//! Read-only register file Version at address 0x4000.
//! A static register file that contains the version number of the register-file.
//! 
//! The version number will be incremented every time a change is made to the
//! verilog register file definitions. This library will only work when the
//! version number is exactly the same as expected.
struct Version
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    Version() = default;
    //! Initialize the single field with a specific value
    Version(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t number() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void number(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x4000;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file Driver at address 0x8000.
//! A static register file that contains the driver version of the Fpga.
//! 
//! It is always `0xcafebabe`. This value is used internally to identify the
//! Fpga. The implementation can only connect to a node with that exact driver
//! version.
struct Driver
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    Driver() = default;
    //! Initialize the single field with a specific value
    Driver(uint64_t value)
    : raw(value & 0xffffffffffffffff) {}

    //! Read the single field
    uint64_t version() const { return raw & 0xffffffffffffffff;};
    //! Set the single field
    void version(uint64_t value) { raw = value; }
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x8000;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};


//! Read-only register file Info at address 0x8008.
//! Extoll specific information register.
//! 
//! It contains a globally unique ID and the node id of the remote node.
//! Note: it is possible that the node id is zero, when the Fpga have been
//! flashed while the network is already running. In that case the node id could
//! be written to the Fpga, as the register is actually read-write.
struct Info
{
    //! The raw bits used to send and receive data to and from the hardware.
    //! This member my be accessed directly. The concrete bit-fields are always
    //! synchronized with this value.
    uint64_t raw = 0;

    //! Initialize all fields with zero
    Info() = default;

    //! Initialize all fields with a specific value
    Info(uint32_t guid_, uint32_t node_id_)
    {
        raw |= (uint64_t(guid_) & 0xffffff) << 0;
        raw |= (uint64_t(node_id_) & 0xffff) << 24;
    }
    
    //! Read the `guid` field
    uint32_t guid() const { return uint32_t(raw >> 0 & 0xffffff);}
    //! Read the `node_id` field
    uint32_t node_id() const { return uint32_t(raw >> 24 & 0xffff);}

    
    //! Set the `guid` field
    void guid(uint32_t value) { raw &= ~(0xffffffull << 0); raw |= (uint64_t(value) & 0xffffff) << 0;}
    //! Set the `node_id` field
    void node_id(uint32_t value) { raw &= ~(0xffffull << 24); raw |= (uint64_t(value) & 0xffff) << 24;}
    
    //! The hardware address of the register file on the remote Fpga
    constexpr static RMA2_NLA ADDRESS = 0x8008;
    //! Indicates whether this field can be read on the software side
    constexpr static bool READABLE = true;
    //! Indicates whether this field can be written on the software side
    constexpr static bool WRITABLE = false;
};





}
}
}