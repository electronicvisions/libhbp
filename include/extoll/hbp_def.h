/**
 * This is a generated file - do not change it
 * 2019-03-27 20:31:51.984518
 */

#pragma once

#include <cinttypes>

#include <extoll/rma.h>


namespace extoll {
namespace library {
namespace rf {



struct Reset
{
    
    // core : 1
    // hicann : 1
    // arq : 1
    // pulse_mem : 1

    uint64_t raw = 0;

    Reset() = default;

    Reset(bool core_, bool hicann_, bool arq_, bool pulse_mem_)
    {
        
        raw |= (uint64_t(core_) & 0x1) << 0;
        raw |= (uint64_t(hicann_) & 0x1) << 1;
        raw |= (uint64_t(arq_) & 0x1) << 2;
        raw |= (uint64_t(pulse_mem_) & 0x1) << 3;
    }

    bool core() const { return bool(raw >> 0 & 0x1);}
    bool hicann() const { return bool(raw >> 1 & 0x1);}
    bool arq() const { return bool(raw >> 2 & 0x1);}
    bool pulse_mem() const { return bool(raw >> 3 & 0x1);}


    void core(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    void hicann(bool value) { raw &= ~(0x1ull << 1); raw |= (uint64_t(value) & 0x1) << 1;}
    void arq(bool value) { raw &= ~(0x1ull << 2); raw |= (uint64_t(value) & 0x1) << 2;}
    void pulse_mem(bool value) { raw &= ~(0x1ull << 3); raw |= (uint64_t(value) & 0x1) << 3;}

    constexpr static RMA2_NLA ADDRESS = 0x0;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct JtagCmd
{
    
    // type : 3
    // length : 10
    // pause : 1
    // execute : 1

    uint64_t raw = 0;
    enum class Type
    {
    
        Reset = 0,
        IR = 1,
        DR = 2,
        EnableClock = 4,
        DisableClock = 5,
    };
    constexpr static Type Reset = Type::Reset;
    constexpr static Type IR = Type::IR;
    constexpr static Type DR = Type::DR;
    constexpr static Type EnableClock = Type::EnableClock;
    constexpr static Type DisableClock = Type::DisableClock;

    JtagCmd() = default;

    JtagCmd(Type type_, uint32_t length_, bool pause_, bool execute_)
    {
        
        raw |= (uint64_t(type_) & 0x7) << 0;
        raw |= (uint64_t(length_) & 0x3ff) << 3;
        raw |= (uint64_t(pause_) & 0x1) << 13;
        raw |= (uint64_t(execute_) & 0x1) << 14;
    }

    Type type() const { return Type(raw >> 0 & 0x7);}
    uint32_t length() const { return uint32_t(raw >> 3 & 0x3ff);}
    bool pause() const { return bool(raw >> 13 & 0x1);}
    bool execute() const { return bool(raw >> 14 & 0x1);}


    void type(Type value) { raw &= ~(0x7ull << 0); raw |= (uint64_t(value) & 0x7) << 0;}
    void length(uint32_t value) { raw &= ~(0x3ffull << 3); raw |= (uint64_t(value) & 0x3ff) << 3;}
    void pause(bool value) { raw &= ~(0x1ull << 13); raw |= (uint64_t(value) & 0x1) << 13;}
    void execute(bool value) { raw &= ~(0x1ull << 14); raw |= (uint64_t(value) & 0x1) << 14;}

    constexpr static RMA2_NLA ADDRESS = 0x400;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct JtagStatus
{
    
    // clock_enabled : 1
    // paused : 1

    uint64_t raw = 0;

    JtagStatus() = default;

    JtagStatus(bool clock_enabled_, bool paused_)
    {
        
        raw |= (uint64_t(clock_enabled_) & 0x1) << 0;
        raw |= (uint64_t(paused_) & 0x1) << 1;
    }

    bool clock_enabled() const { return bool(raw >> 0 & 0x1);}
    bool paused() const { return bool(raw >> 1 & 0x1);}


    void clock_enabled(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    void paused(bool value) { raw &= ~(0x1ull << 1); raw |= (uint64_t(value) & 0x1) << 1;}

    constexpr static RMA2_NLA ADDRESS = 0x408;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct JtagSend
{
    
    // data : 64

    uint64_t raw = 0;

    JtagSend() = default;
    JtagSend(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x480;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct JtagReceive
{
    
    // data : 64

    uint64_t raw = 0;

    JtagReceive() = default;
    JtagReceive(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x500;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HicannIfState
{
    
    // channel_status : 8
    // crc_count : 8
    // systime : 14

    uint64_t raw = 0;

    HicannIfState() = default;

    HicannIfState(uint32_t channel_status_, uint32_t crc_count_, uint32_t systime_)
    {
        
        raw |= (uint64_t(channel_status_) & 0xff) << 0;
        raw |= (uint64_t(crc_count_) & 0xff) << 8;
        raw |= (uint64_t(systime_) & 0x3fff) << 16;
    }

    uint32_t channel_status() const { return uint32_t(raw >> 0 & 0xff);}
    uint32_t crc_count() const { return uint32_t(raw >> 8 & 0xff);}
    uint32_t systime() const { return uint32_t(raw >> 16 & 0x3fff);}


    void channel_status(uint32_t value) { raw &= ~(0xffull << 0); raw |= (uint64_t(value) & 0xff) << 0;}
    void crc_count(uint32_t value) { raw &= ~(0xffull << 8); raw |= (uint64_t(value) & 0xff) << 8;}
    void systime(uint32_t value) { raw &= ~(0x3fffull << 16); raw |= (uint64_t(value) & 0x3fff) << 16;}

    constexpr static RMA2_NLA ADDRESS = 0x800;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HicannIfRxConfig
{
    
    // data : 64

    uint64_t raw = 0;

    HicannIfRxConfig() = default;
    HicannIfRxConfig(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x808;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HicannIfRxPulse
{
    
    // data : 24

    uint64_t raw = 0;

    HicannIfRxPulse() = default;

    HicannIfRxPulse(uint32_t data_)
    {
        
        raw |= (uint64_t(data_) & 0xffffff) << 0;
    }

    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffff);}


    void data(uint32_t value) { raw &= ~(0xffffffull << 0); raw |= (uint64_t(value) & 0xffffff) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x810;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HicannIfConfig
{
    
    // start_link : 1
    // loopback_enable : 1
    // auto_init : 1
    // init_master : 1
    // use_timestamp : 1
    // auto_limit : 1
    // pulse_protocol : 1
    // config_protocol : 1
    // heap_mode : 8
    // limit : 11
    // dc_coding : 1

    uint64_t raw = 0;

    HicannIfConfig() = default;

    HicannIfConfig(bool start_link_, bool loopback_enable_, bool auto_init_, bool init_master_, bool use_timestamp_, bool auto_limit_, bool pulse_protocol_, bool config_protocol_, uint32_t heap_mode_, uint32_t limit_, bool dc_coding_)
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
    }

    bool start_link() const { return bool(raw >> 0 & 0x1);}
    bool loopback_enable() const { return bool(raw >> 1 & 0x1);}
    bool auto_init() const { return bool(raw >> 2 & 0x1);}
    bool init_master() const { return bool(raw >> 3 & 0x1);}
    bool use_timestamp() const { return bool(raw >> 4 & 0x1);}
    bool auto_limit() const { return bool(raw >> 5 & 0x1);}
    bool pulse_protocol() const { return bool(raw >> 6 & 0x1);}
    bool config_protocol() const { return bool(raw >> 7 & 0x1);}
    uint32_t heap_mode() const { return uint32_t(raw >> 8 & 0xff);}
    uint32_t limit() const { return uint32_t(raw >> 16 & 0x7ff);}
    bool dc_coding() const { return bool(raw >> 27 & 0x1);}


    void start_link(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    void loopback_enable(bool value) { raw &= ~(0x1ull << 1); raw |= (uint64_t(value) & 0x1) << 1;}
    void auto_init(bool value) { raw &= ~(0x1ull << 2); raw |= (uint64_t(value) & 0x1) << 2;}
    void init_master(bool value) { raw &= ~(0x1ull << 3); raw |= (uint64_t(value) & 0x1) << 3;}
    void use_timestamp(bool value) { raw &= ~(0x1ull << 4); raw |= (uint64_t(value) & 0x1) << 4;}
    void auto_limit(bool value) { raw &= ~(0x1ull << 5); raw |= (uint64_t(value) & 0x1) << 5;}
    void pulse_protocol(bool value) { raw &= ~(0x1ull << 6); raw |= (uint64_t(value) & 0x1) << 6;}
    void config_protocol(bool value) { raw &= ~(0x1ull << 7); raw |= (uint64_t(value) & 0x1) << 7;}
    void heap_mode(uint32_t value) { raw &= ~(0xffull << 8); raw |= (uint64_t(value) & 0xff) << 8;}
    void limit(uint32_t value) { raw &= ~(0x7ffull << 16); raw |= (uint64_t(value) & 0x7ff) << 16;}
    void dc_coding(bool value) { raw &= ~(0x1ull << 27); raw |= (uint64_t(value) & 0x1) << 27;}

    constexpr static RMA2_NLA ADDRESS = 0x818;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct HicannIfControls
{
    
    // tx_hicann_pulse_enable : 1
    // tx_hicann_config_enable : 1
    // routing_data_enable : 1
    // channel_reset : 1
    // crc_count_reset : 1

    uint64_t raw = 0;

    HicannIfControls() = default;

    HicannIfControls(bool tx_hicann_pulse_enable_, bool tx_hicann_config_enable_, bool routing_data_enable_, bool channel_reset_, bool crc_count_reset_)
    {
        
        raw |= (uint64_t(tx_hicann_pulse_enable_) & 0x1) << 0;
        raw |= (uint64_t(tx_hicann_config_enable_) & 0x1) << 1;
        raw |= (uint64_t(routing_data_enable_) & 0x1) << 2;
        raw |= (uint64_t(channel_reset_) & 0x1) << 3;
        raw |= (uint64_t(crc_count_reset_) & 0x1) << 4;
    }

    bool tx_hicann_pulse_enable() const { return bool(raw >> 0 & 0x1);}
    bool tx_hicann_config_enable() const { return bool(raw >> 1 & 0x1);}
    bool routing_data_enable() const { return bool(raw >> 2 & 0x1);}
    bool channel_reset() const { return bool(raw >> 3 & 0x1);}
    bool crc_count_reset() const { return bool(raw >> 4 & 0x1);}


    void tx_hicann_pulse_enable(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}
    void tx_hicann_config_enable(bool value) { raw &= ~(0x1ull << 1); raw |= (uint64_t(value) & 0x1) << 1;}
    void routing_data_enable(bool value) { raw &= ~(0x1ull << 2); raw |= (uint64_t(value) & 0x1) << 2;}
    void channel_reset(bool value) { raw &= ~(0x1ull << 3); raw |= (uint64_t(value) & 0x1) << 3;}
    void crc_count_reset(bool value) { raw &= ~(0x1ull << 4); raw |= (uint64_t(value) & 0x1) << 4;}

    constexpr static RMA2_NLA ADDRESS = 0x820;
    constexpr static bool READABLE = false;
    constexpr static bool WRITABLE = true;
};


struct HicannIfTxData
{
    
    // data : 64

    uint64_t raw = 0;

    HicannIfTxData() = default;
    HicannIfTxData(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x828;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct HicannPacketGen
{
    
    // count : 25
    // error : 1
    // enable : 1

    uint64_t raw = 0;

    HicannPacketGen() = default;

    HicannPacketGen(uint32_t count_, bool error_, bool enable_)
    {
        
        raw |= (uint64_t(count_) & 0x1ffffff) << 0;
        raw |= (uint64_t(error_) & 0x1) << 25;
        raw |= (uint64_t(enable_) & 0x1) << 26;
    }

    uint32_t count() const { return uint32_t(raw >> 0 & 0x1ffffff);}
    bool error() const { return bool(raw >> 25 & 0x1);}
    bool enable() const { return bool(raw >> 26 & 0x1);}


    void count(uint32_t value) { raw &= ~(0x1ffffffull << 0); raw |= (uint64_t(value) & 0x1ffffff) << 0;}
    void error(bool value) { raw &= ~(0x1ull << 25); raw |= (uint64_t(value) & 0x1) << 25;}
    void enable(bool value) { raw &= ~(0x1ull << 26); raw |= (uint64_t(value) & 0x1) << 26;}

    constexpr static RMA2_NLA ADDRESS = 0x830;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct HicannChannel
{
    
    // number : 3

    uint64_t raw = 0;

    HicannChannel() = default;

    HicannChannel(uint32_t number_)
    {
        
        raw |= (uint64_t(number_) & 0x7) << 0;
    }

    uint32_t number() const { return uint32_t(raw >> 0 & 0x7);}


    void number(uint32_t value) { raw &= ~(0x7ull << 0); raw |= (uint64_t(value) & 0x7) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x838;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct ArqTimings
{
    
    // master_timeout : 10
    // target_timeout : 10
    // arbiter_delay : 5
    // bit : 1

    uint64_t raw = 0;

    ArqTimings() = default;

    ArqTimings(uint32_t master_timeout_, uint32_t target_timeout_, uint32_t arbiter_delay_, bool bit_)
    {
        
        raw |= (uint64_t(master_timeout_) & 0x3ff) << 0;
        raw |= (uint64_t(target_timeout_) & 0x3ff) << 10;
        raw |= (uint64_t(arbiter_delay_) & 0x1f) << 20;
        raw |= (uint64_t(bit_) & 0x1) << 25;
    }

    uint32_t master_timeout() const { return uint32_t(raw >> 0 & 0x3ff);}
    uint32_t target_timeout() const { return uint32_t(raw >> 10 & 0x3ff);}
    uint32_t arbiter_delay() const { return uint32_t(raw >> 20 & 0x1f);}
    bool bit() const { return bool(raw >> 25 & 0x1);}


    void master_timeout(uint32_t value) { raw &= ~(0x3ffull << 0); raw |= (uint64_t(value) & 0x3ff) << 0;}
    void target_timeout(uint32_t value) { raw &= ~(0x3ffull << 10); raw |= (uint64_t(value) & 0x3ff) << 10;}
    void arbiter_delay(uint32_t value) { raw &= ~(0x1full << 20); raw |= (uint64_t(value) & 0x1f) << 20;}
    void bit(bool value) { raw &= ~(0x1ull << 25); raw |= (uint64_t(value) & 0x1) << 25;}

    constexpr static RMA2_NLA ADDRESS = 0x840;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TestControlEnable
{
    
    // enable : 1

    uint64_t raw = 0;

    TestControlEnable() = default;

    TestControlEnable(bool enable_)
    {
        
        raw |= (uint64_t(enable_) & 0x1) << 0;
    }

    bool enable() const { return bool(raw >> 0 & 0x1);}


    void enable(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0xc00;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TestControlConfig
{
    
    // quad_words : 8
    // pause_time : 8
    // count_up : 1

    uint64_t raw = 0;

    TestControlConfig() = default;

    TestControlConfig(uint32_t quad_words_, uint32_t pause_time_, bool count_up_)
    {
        
        raw |= (uint64_t(quad_words_) & 0xff) << 0;
        raw |= (uint64_t(pause_time_) & 0xff) << 8;
        raw |= (uint64_t(count_up_) & 0x1) << 16;
    }

    uint32_t quad_words() const { return uint32_t(raw >> 0 & 0xff);}
    uint32_t pause_time() const { return uint32_t(raw >> 8 & 0xff);}
    bool count_up() const { return bool(raw >> 16 & 0x1);}


    void quad_words(uint32_t value) { raw &= ~(0xffull << 0); raw |= (uint64_t(value) & 0xff) << 0;}
    void pause_time(uint32_t value) { raw &= ~(0xffull << 8); raw |= (uint64_t(value) & 0xff) << 8;}
    void count_up(bool value) { raw &= ~(0x1ull << 16); raw |= (uint64_t(value) & 0x1) << 16;}

    constexpr static RMA2_NLA ADDRESS = 0xc08;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TestControlStart
{
    
    // start : 1

    uint64_t raw = 0;

    TestControlStart() = default;

    TestControlStart(bool start_)
    {
        
        raw |= (uint64_t(start_) & 0x1) << 0;
    }

    bool start() const { return bool(raw >> 0 & 0x1);}


    void start(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0xc10;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TestControlData
{
    
    // data : 64

    uint64_t raw = 0;

    TestControlData() = default;
    TestControlData(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0xc18;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TestControlType
{
    
    // type : 16

    uint64_t raw = 0;
    enum class Type : uint16_t
    {
    
        TracePulse = 3237,
        FpgaConfig = 3099,
        HicannConfig = 10779,
    };
    constexpr static Type TracePulse = Type::TracePulse;
    constexpr static Type FpgaConfig = Type::FpgaConfig;
    constexpr static Type HicannConfig = Type::HicannConfig;

    TestControlType() = default;

    TestControlType(Type type_)
    {
        
        raw |= (uint64_t(type_) & 0xffff) << 0;
    }

    Type type() const { return Type(raw >> 0 & 0xffff);}


    void type(Type value) { raw &= ~(0xffffull << 0); raw |= (uint64_t(value) & 0xffff) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0xc20;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TraceBufferStart
{
    
    // data : 64

    uint64_t raw = 0;

    TraceBufferStart() = default;
    TraceBufferStart(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1000;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TraceBufferSize
{
    
    // data : 32

    uint64_t raw = 0;

    TraceBufferSize() = default;

    TraceBufferSize(uint32_t data_)
    {
        
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }

    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}


    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x1008;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TraceBufferFullThreshold
{
    
    // data : 32

    uint64_t raw = 0;

    TraceBufferFullThreshold() = default;

    TraceBufferFullThreshold(uint32_t data_)
    {
        
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }

    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}


    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x1010;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TraceBufferCounter
{
    
    // start_address : 16
    // size : 16
    // threshold : 16
    // wraps : 16

    uint64_t raw = 0;

    TraceBufferCounter() = default;

    TraceBufferCounter(uint32_t start_address_, uint32_t size_, uint32_t threshold_, uint32_t wraps_)
    {
        
        raw |= (uint64_t(start_address_) & 0xffff) << 0;
        raw |= (uint64_t(size_) & 0xffff) << 16;
        raw |= (uint64_t(threshold_) & 0xffff) << 32;
        raw |= (uint64_t(wraps_) & 0xffff) << 48;
    }

    uint32_t start_address() const { return uint32_t(raw >> 0 & 0xffff);}
    uint32_t size() const { return uint32_t(raw >> 16 & 0xffff);}
    uint32_t threshold() const { return uint32_t(raw >> 32 & 0xffff);}
    uint32_t wraps() const { return uint32_t(raw >> 48 & 0xffff);}


    void start_address(uint32_t value) { raw &= ~(0xffffull << 0); raw |= (uint64_t(value) & 0xffff) << 0;}
    void size(uint32_t value) { raw &= ~(0xffffull << 16); raw |= (uint64_t(value) & 0xffff) << 16;}
    void threshold(uint32_t value) { raw &= ~(0xffffull << 32); raw |= (uint64_t(value) & 0xffff) << 32;}
    void wraps(uint32_t value) { raw &= ~(0xffffull << 48); raw |= (uint64_t(value) & 0xffff) << 48;}

    constexpr static RMA2_NLA ADDRESS = 0x1018;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct TraceBufferCounterReset
{
    
    // reset : 1

    uint64_t raw = 0;

    TraceBufferCounterReset() = default;

    TraceBufferCounterReset(bool reset_)
    {
        
        raw |= (uint64_t(reset_) & 0x1) << 0;
    }

    bool reset() const { return bool(raw >> 0 & 0x1);}


    void reset(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x1020;
    constexpr static bool READABLE = false;
    constexpr static bool WRITABLE = true;
};


struct TraceBufferCurrentAddress
{
    
    // data : 64

    uint64_t raw = 0;

    TraceBufferCurrentAddress() = default;
    TraceBufferCurrentAddress(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1028;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct TraceBufferEndAddress
{
    
    // data : 64

    uint64_t raw = 0;

    TraceBufferEndAddress() = default;
    TraceBufferEndAddress(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1030;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct TraceBufferFreeSpace
{
    
    // data : 32

    uint64_t raw = 0;

    TraceBufferFreeSpace() = default;

    TraceBufferFreeSpace(uint32_t data_)
    {
        
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }

    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}


    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x1038;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct TraceBufferInit
{
    
    // start : 1

    uint64_t raw = 0;

    TraceBufferInit() = default;

    TraceBufferInit(bool start_)
    {
        
        raw |= (uint64_t(start_) & 0x1) << 0;
    }

    bool start() const { return bool(raw >> 0 & 0x1);}


    void start(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x1040;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct HicannBufferStart
{
    
    // data : 64

    uint64_t raw = 0;

    HicannBufferStart() = default;
    HicannBufferStart(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1080;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct HicannBufferSize
{
    
    // data : 32

    uint64_t raw = 0;

    HicannBufferSize() = default;

    HicannBufferSize(uint32_t data_)
    {
        
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }

    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}


    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x1088;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct HicannBufferFullThreshold
{
    
    // data : 32

    uint64_t raw = 0;

    HicannBufferFullThreshold() = default;

    HicannBufferFullThreshold(uint32_t data_)
    {
        
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }

    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}


    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x1090;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct HicannBufferCounter
{
    
    // start_address : 16
    // size : 16
    // threshold : 16
    // wraps : 16

    uint64_t raw = 0;

    HicannBufferCounter() = default;

    HicannBufferCounter(uint32_t start_address_, uint32_t size_, uint32_t threshold_, uint32_t wraps_)
    {
        
        raw |= (uint64_t(start_address_) & 0xffff) << 0;
        raw |= (uint64_t(size_) & 0xffff) << 16;
        raw |= (uint64_t(threshold_) & 0xffff) << 32;
        raw |= (uint64_t(wraps_) & 0xffff) << 48;
    }

    uint32_t start_address() const { return uint32_t(raw >> 0 & 0xffff);}
    uint32_t size() const { return uint32_t(raw >> 16 & 0xffff);}
    uint32_t threshold() const { return uint32_t(raw >> 32 & 0xffff);}
    uint32_t wraps() const { return uint32_t(raw >> 48 & 0xffff);}


    void start_address(uint32_t value) { raw &= ~(0xffffull << 0); raw |= (uint64_t(value) & 0xffff) << 0;}
    void size(uint32_t value) { raw &= ~(0xffffull << 16); raw |= (uint64_t(value) & 0xffff) << 16;}
    void threshold(uint32_t value) { raw &= ~(0xffffull << 32); raw |= (uint64_t(value) & 0xffff) << 32;}
    void wraps(uint32_t value) { raw &= ~(0xffffull << 48); raw |= (uint64_t(value) & 0xffff) << 48;}

    constexpr static RMA2_NLA ADDRESS = 0x1098;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HicannBufferCounterReset
{
    
    // reset : 1

    uint64_t raw = 0;

    HicannBufferCounterReset() = default;

    HicannBufferCounterReset(bool reset_)
    {
        
        raw |= (uint64_t(reset_) & 0x1) << 0;
    }

    bool reset() const { return bool(raw >> 0 & 0x1);}


    void reset(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x10a0;
    constexpr static bool READABLE = false;
    constexpr static bool WRITABLE = true;
};


struct HicannBufferCurrentAddress
{
    
    // data : 64

    uint64_t raw = 0;

    HicannBufferCurrentAddress() = default;
    HicannBufferCurrentAddress(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x10a8;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HicannBufferEndAddress
{
    
    // data : 64

    uint64_t raw = 0;

    HicannBufferEndAddress() = default;
    HicannBufferEndAddress(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t data() const { return raw & 0xffffffffffffffff;};
    void data(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x10b0;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HicannBufferFreeSpace
{
    
    // data : 32

    uint64_t raw = 0;

    HicannBufferFreeSpace() = default;

    HicannBufferFreeSpace(uint32_t data_)
    {
        
        raw |= (uint64_t(data_) & 0xffffffff) << 0;
    }

    uint32_t data() const { return uint32_t(raw >> 0 & 0xffffffff);}


    void data(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x10b8;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HicannBufferInit
{
    
    // start : 1

    uint64_t raw = 0;

    HicannBufferInit() = default;

    HicannBufferInit(bool start_)
    {
        
        raw |= (uint64_t(start_) & 0x1) << 0;
    }

    bool start() const { return bool(raw >> 0 & 0x1);}


    void start(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x10c0;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct RraPutReceived
{
    
    // count : 48

    uint64_t raw = 0;

    RraPutReceived() = default;
    RraPutReceived(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1100;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct RraGetReceived
{
    
    // count : 48

    uint64_t raw = 0;

    RraGetReceived() = default;
    RraGetReceived(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1108;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct RmaPutReceived
{
    
    // count : 48

    uint64_t raw = 0;

    RmaPutReceived() = default;
    RmaPutReceived(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1110;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct RmaNotificationReceived
{
    
    // count : 48

    uint64_t raw = 0;

    RmaNotificationReceived() = default;
    RmaNotificationReceived(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1118;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct PlaybackReceived
{
    
    // count : 48

    uint64_t raw = 0;

    PlaybackReceived() = default;
    PlaybackReceived(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1120;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct FpgaConfigReceived
{
    
    // count : 48

    uint64_t raw = 0;

    FpgaConfigReceived() = default;
    FpgaConfigReceived(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1128;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HicannConfigReceived
{
    
    // count : 48

    uint64_t raw = 0;

    HicannConfigReceived() = default;
    HicannConfigReceived(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1130;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct JtagDataReceived
{
    
    // count : 48

    uint64_t raw = 0;

    JtagDataReceived() = default;
    JtagDataReceived(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1138;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct NeighbourDataReceived
{
    
    // count : 48

    uint64_t raw = 0;

    NeighbourDataReceived() = default;
    NeighbourDataReceived(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1140;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct CounterReset
{
    
    // reset : 1

    uint64_t raw = 0;

    CounterReset() = default;

    CounterReset(bool reset_)
    {
        
        raw |= (uint64_t(reset_) & 0x1) << 0;
    }

    bool reset() const { return bool(raw >> 0 & 0x1);}


    void reset(bool value) { raw &= ~(0x1ull << 0); raw |= (uint64_t(value) & 0x1) << 0;}

    constexpr static RMA2_NLA ADDRESS = 0x1148;
    constexpr static bool READABLE = false;
    constexpr static bool WRITABLE = true;
};


struct InvalidCommand
{
    
    // count : 48

    uint64_t raw = 0;

    InvalidCommand() = default;
    InvalidCommand(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1150;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct InvalidType
{
    
    // count : 48

    uint64_t raw = 0;

    InvalidType() = default;
    InvalidType(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1158;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct InvalidPayloadSize
{
    
    // count : 48

    uint64_t raw = 0;

    InvalidPayloadSize() = default;
    InvalidPayloadSize(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1160;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct InvalidFields
{
    
    // count : 48

    uint64_t raw = 0;

    InvalidFields() = default;
    InvalidFields(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1168;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct InvalidMode
{
    
    // count : 48

    uint64_t raw = 0;

    InvalidMode() = default;
    InvalidMode(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1170;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct InvalidRraAddress
{
    
    // count : 48

    uint64_t raw = 0;

    InvalidRraAddress() = default;
    InvalidRraAddress(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1178;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct InvalidHost
{
    
    // count : 48

    uint64_t raw = 0;

    InvalidHost() = default;
    InvalidHost(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1180;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct ConfigAddressReinit
{
    
    // count : 48

    uint64_t raw = 0;

    ConfigAddressReinit() = default;
    ConfigAddressReinit(uint64_t value)
        : raw(value & 0xffffffffffff) {}

    uint64_t count() const { return raw & 0xffffffffffff;};
    void count(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1188;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct HostEndpoint
{
    
    // node_id : 16
    // protection_domain : 16
    // vpid : 10
    // mode : 6

    uint64_t raw = 0;

    HostEndpoint() = default;

    HostEndpoint(uint32_t node_id_, uint32_t protection_domain_, uint32_t vpid_, uint32_t mode_)
    {
        
        raw |= (uint64_t(node_id_) & 0xffff) << 0;
        raw |= (uint64_t(protection_domain_) & 0xffff) << 16;
        raw |= (uint64_t(vpid_) & 0x3ff) << 32;
        raw |= (uint64_t(mode_) & 0x3f) << 42;
    }

    uint32_t node_id() const { return uint32_t(raw >> 0 & 0xffff);}
    uint32_t protection_domain() const { return uint32_t(raw >> 16 & 0xffff);}
    uint32_t vpid() const { return uint32_t(raw >> 32 & 0x3ff);}
    uint32_t mode() const { return uint32_t(raw >> 42 & 0x3f);}


    void node_id(uint32_t value) { raw &= ~(0xffffull << 0); raw |= (uint64_t(value) & 0xffff) << 0;}
    void protection_domain(uint32_t value) { raw &= ~(0xffffull << 16); raw |= (uint64_t(value) & 0xffff) << 16;}
    void vpid(uint32_t value) { raw &= ~(0x3ffull << 32); raw |= (uint64_t(value) & 0x3ff) << 32;}
    void mode(uint32_t value) { raw &= ~(0x3full << 42); raw |= (uint64_t(value) & 0x3f) << 42;}

    constexpr static RMA2_NLA ADDRESS = 0x1190;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct ConfigResponse
{
    
    // address : 64

    uint64_t raw = 0;

    ConfigResponse() = default;
    ConfigResponse(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t address() const { return raw & 0xffffffffffffffff;};
    void address(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x1198;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct TraceNotificationBehaviour
{
    
    // timeout : 32
    // frequency : 32

    uint64_t raw = 0;

    TraceNotificationBehaviour() = default;

    TraceNotificationBehaviour(uint32_t timeout_, uint32_t frequency_)
    {
        
        raw |= (uint64_t(timeout_) & 0xffffffff) << 0;
        raw |= (uint64_t(frequency_) & 0xffffffff) << 32;
    }

    uint32_t timeout() const { return uint32_t(raw >> 0 & 0xffffffff);}
    uint32_t frequency() const { return uint32_t(raw >> 32 & 0xffffffff);}


    void timeout(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    void frequency(uint32_t value) { raw &= ~(0xffffffffull << 32); raw |= (uint64_t(value) & 0xffffffff) << 32;}

    constexpr static RMA2_NLA ADDRESS = 0x11a0;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct HicannNotificationBehaviour
{
    
    // timeout : 32
    // frequency : 32

    uint64_t raw = 0;

    HicannNotificationBehaviour() = default;

    HicannNotificationBehaviour(uint32_t timeout_, uint32_t frequency_)
    {
        
        raw |= (uint64_t(timeout_) & 0xffffffff) << 0;
        raw |= (uint64_t(frequency_) & 0xffffffff) << 32;
    }

    uint32_t timeout() const { return uint32_t(raw >> 0 & 0xffffffff);}
    uint32_t frequency() const { return uint32_t(raw >> 32 & 0xffffffff);}


    void timeout(uint32_t value) { raw &= ~(0xffffffffull << 0); raw |= (uint64_t(value) & 0xffffffff) << 0;}
    void frequency(uint32_t value) { raw &= ~(0xffffffffull << 32); raw |= (uint64_t(value) & 0xffffffff) << 32;}

    constexpr static RMA2_NLA ADDRESS = 0x11a8;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = true;
};


struct Driver
{
    
    // version : 64

    uint64_t raw = 0;

    Driver() = default;
    Driver(uint64_t value)
        : raw(value & 0xffffffffffffffff) {}

    uint64_t version() const { return raw & 0xffffffffffffffff;};
    void version(uint64_t value) { raw = value; }

    constexpr static RMA2_NLA ADDRESS = 0x8000;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};


struct Info
{
    
    // guid : 24
    // node_id : 16

    uint64_t raw = 0;

    Info() = default;

    Info(uint32_t guid_, uint32_t node_id_)
    {
        
        raw |= (uint64_t(guid_) & 0xffffff) << 0;
        raw |= (uint64_t(node_id_) & 0xffff) << 24;
    }

    uint32_t guid() const { return uint32_t(raw >> 0 & 0xffffff);}
    uint32_t node_id() const { return uint32_t(raw >> 24 & 0xffff);}


    void guid(uint32_t value) { raw &= ~(0xffffffull << 0); raw |= (uint64_t(value) & 0xffffff) << 0;}
    void node_id(uint32_t value) { raw &= ~(0xffffull << 24); raw |= (uint64_t(value) & 0xffff) << 24;}

    constexpr static RMA2_NLA ADDRESS = 0x8008;
    constexpr static bool READABLE = true;
    constexpr static bool WRITABLE = false;
};





}
}
}