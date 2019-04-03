/*
 * This is a generated file - do not change it
 * 2019-04-02 17:47:04.588305
 */

#include <catch.hpp>

#include <extoll/rf_definitions.h>

using namespace extoll::library::rf;



TEST_CASE("Definition 'Reset'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        Reset rf {false, false, false, false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.core());
        REQUIRE(!rf.hicann());
        REQUIRE(!rf.arq());
        REQUIRE(!rf.pulse_mem());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.core());
        REQUIRE(rf.hicann());
        REQUIRE(rf.arq());
        REQUIRE(rf.pulse_mem());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.core());
        REQUIRE(rf.hicann());
        REQUIRE(!rf.arq());
        REQUIRE(rf.pulse_mem());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.core());
        REQUIRE(!rf.hicann());
        REQUIRE(rf.arq());
        REQUIRE(!rf.pulse_mem());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.core());
        REQUIRE(rf.hicann());
        REQUIRE(rf.arq());
        REQUIRE(rf.pulse_mem());
        
    }

    SECTION("write fields - read raw")
    {
        Reset rf {false, false, false, false};

        
        
        rf.core(false);
        rf.hicann(false);
        rf.arq(false);
        rf.pulse_mem(false);
        REQUIRE((rf.raw & 0xfu) == 0x0);
        
        rf.core(true);
        rf.hicann(true);
        rf.arq(true);
        rf.pulse_mem(true);
        REQUIRE((rf.raw & 0xfu) == 0xf);
        
        rf.core(false);
        rf.hicann(true);
        rf.arq(false);
        rf.pulse_mem(true);
        REQUIRE((rf.raw & 0xfu) == 0xa);
        
        rf.core(true);
        rf.hicann(false);
        rf.arq(true);
        rf.pulse_mem(false);
        REQUIRE((rf.raw & 0xfu) == 0x5);
        
        rf.core(true);
        rf.hicann(true);
        rf.arq(true);
        rf.pulse_mem(true);
        REQUIRE((rf.raw & 0xfu) == 0xf);
    }
}

TEST_CASE("Definition 'JtagCmd'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        JtagCmd rf {JtagCmd::Type(0), 0, false, false};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x0));
        REQUIRE(rf.length() == 0x0u);
        REQUIRE(!rf.pause());
        REQUIRE(!rf.execute());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x7));
        REQUIRE(rf.length() == 0x3ffu);
        REQUIRE(rf.pause());
        REQUIRE(rf.execute());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x2));
        REQUIRE(rf.length() == 0x155u);
        REQUIRE(rf.pause());
        REQUIRE(!rf.execute());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x5));
        REQUIRE(rf.length() == 0x2aau);
        REQUIRE(!rf.pause());
        REQUIRE(rf.execute());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x7));
        REQUIRE(rf.length() == 0x3ddu);
        REQUIRE(rf.pause());
        REQUIRE(!rf.execute());
        
    }

    SECTION("write fields - read raw")
    {
        JtagCmd rf {JtagCmd::Type(0), 0, false, false};

        
        
        rf.type(JtagCmd::Type(0x0));
        rf.length(0x0);
        rf.pause(false);
        rf.execute(false);
        REQUIRE((rf.raw & 0x7fffu) == 0x0);
        
        rf.type(JtagCmd::Type(0x7));
        rf.length(0x3ff);
        rf.pause(true);
        rf.execute(true);
        REQUIRE((rf.raw & 0x7fffu) == 0x7fff);
        
        rf.type(JtagCmd::Type(0x2));
        rf.length(0x155);
        rf.pause(true);
        rf.execute(false);
        REQUIRE((rf.raw & 0x7fffu) == 0x2aaa);
        
        rf.type(JtagCmd::Type(0x5));
        rf.length(0x2aa);
        rf.pause(false);
        rf.execute(true);
        REQUIRE((rf.raw & 0x7fffu) == 0x5555);
        
        rf.type(JtagCmd::Type(0x7));
        rf.length(0x3dd);
        rf.pause(true);
        rf.execute(false);
        REQUIRE((rf.raw & 0x7fffu) == 0x3eef);
    }
}

TEST_CASE("Definition 'JtagStatus'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        JtagStatus rf {false, false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.clock_enabled());
        REQUIRE(!rf.paused());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.clock_enabled());
        REQUIRE(rf.paused());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.clock_enabled());
        REQUIRE(rf.paused());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.clock_enabled());
        REQUIRE(!rf.paused());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.clock_enabled());
        REQUIRE(rf.paused());
        
    }

    SECTION("write fields - read raw")
    {
        JtagStatus rf {false, false};

        
        
        rf.clock_enabled(false);
        rf.paused(false);
        REQUIRE((rf.raw & 0x3u) == 0x0);
        
        rf.clock_enabled(true);
        rf.paused(true);
        REQUIRE((rf.raw & 0x3u) == 0x3);
        
        rf.clock_enabled(false);
        rf.paused(true);
        REQUIRE((rf.raw & 0x3u) == 0x2);
        
        rf.clock_enabled(true);
        rf.paused(false);
        REQUIRE((rf.raw & 0x3u) == 0x1);
        
        rf.clock_enabled(true);
        rf.paused(true);
        REQUIRE((rf.raw & 0x3u) == 0x3);
    }
}

TEST_CASE("Definition 'HicannIfState'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfState rf {0, 0, 0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.channel_status() == 0x0u);
        REQUIRE(rf.crc_count() == 0x0u);
        REQUIRE(rf.systime() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.channel_status() == 0xffu);
        REQUIRE(rf.crc_count() == 0xffu);
        REQUIRE(rf.systime() == 0x3fffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.channel_status() == 0xaau);
        REQUIRE(rf.crc_count() == 0xaau);
        REQUIRE(rf.systime() == 0x2aaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.channel_status() == 0x55u);
        REQUIRE(rf.crc_count() == 0x55u);
        REQUIRE(rf.systime() == 0x1555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.channel_status() == 0xefu);
        REQUIRE(rf.crc_count() == 0xbeu);
        REQUIRE(rf.systime() == 0x3abeu);
        
    }

    SECTION("write fields - read raw")
    {
        HicannIfState rf {0, 0, 0};

        
        
        rf.channel_status(0x0);
        rf.crc_count(0x0);
        rf.systime(0x0);
        REQUIRE((rf.raw & 0x3fffffffu) == 0x0);
        
        rf.channel_status(0xff);
        rf.crc_count(0xff);
        rf.systime(0x3fff);
        REQUIRE((rf.raw & 0x3fffffffu) == 0x3fffffff);
        
        rf.channel_status(0xaa);
        rf.crc_count(0xaa);
        rf.systime(0x2aaa);
        REQUIRE((rf.raw & 0x3fffffffu) == 0x2aaaaaaa);
        
        rf.channel_status(0x55);
        rf.crc_count(0x55);
        rf.systime(0x1555);
        REQUIRE((rf.raw & 0x3fffffffu) == 0x15555555);
        
        rf.channel_status(0xef);
        rf.crc_count(0xbe);
        rf.systime(0x3abe);
        REQUIRE((rf.raw & 0x3fffffffu) == 0x3abebeef);
    }
}

TEST_CASE("Definition 'HicannIfRxPulse'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfRxPulse rf {0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.data() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.data() == 0xffffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.data() == 0xaaaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.data() == 0x555555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.data() == 0xbebeefu);
        
    }

    SECTION("write fields - read raw")
    {
        HicannIfRxPulse rf {0};

        
        
        rf.data(0x0);
        REQUIRE((rf.raw & 0xffffffu) == 0x0);
        
        rf.data(0xffffff);
        REQUIRE((rf.raw & 0xffffffu) == 0xffffff);
        
        rf.data(0xaaaaaa);
        REQUIRE((rf.raw & 0xffffffu) == 0xaaaaaa);
        
        rf.data(0x555555);
        REQUIRE((rf.raw & 0xffffffu) == 0x555555);
        
        rf.data(0xbebeef);
        REQUIRE((rf.raw & 0xffffffu) == 0xbebeef);
    }
}

TEST_CASE("Definition 'HicannIfConfig'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfConfig rf {false, false, false, false, false, false, false, false, 0, 0, false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.start_link());
        REQUIRE(!rf.loopback_enable());
        REQUIRE(!rf.auto_init());
        REQUIRE(!rf.init_master());
        REQUIRE(!rf.use_timestamp());
        REQUIRE(!rf.auto_limit());
        REQUIRE(!rf.pulse_protocol());
        REQUIRE(!rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0x0u);
        REQUIRE(rf.limit() == 0x0u);
        REQUIRE(!rf.dc_coding());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.start_link());
        REQUIRE(rf.loopback_enable());
        REQUIRE(rf.auto_init());
        REQUIRE(rf.init_master());
        REQUIRE(rf.use_timestamp());
        REQUIRE(rf.auto_limit());
        REQUIRE(rf.pulse_protocol());
        REQUIRE(rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0xffu);
        REQUIRE(rf.limit() == 0x7ffu);
        REQUIRE(rf.dc_coding());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.start_link());
        REQUIRE(rf.loopback_enable());
        REQUIRE(!rf.auto_init());
        REQUIRE(rf.init_master());
        REQUIRE(!rf.use_timestamp());
        REQUIRE(rf.auto_limit());
        REQUIRE(!rf.pulse_protocol());
        REQUIRE(rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0xaau);
        REQUIRE(rf.limit() == 0x2aau);
        REQUIRE(rf.dc_coding());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.start_link());
        REQUIRE(!rf.loopback_enable());
        REQUIRE(rf.auto_init());
        REQUIRE(!rf.init_master());
        REQUIRE(rf.use_timestamp());
        REQUIRE(!rf.auto_limit());
        REQUIRE(rf.pulse_protocol());
        REQUIRE(!rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0x55u);
        REQUIRE(rf.limit() == 0x555u);
        REQUIRE(!rf.dc_coding());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.start_link());
        REQUIRE(rf.loopback_enable());
        REQUIRE(rf.auto_init());
        REQUIRE(rf.init_master());
        REQUIRE(!rf.use_timestamp());
        REQUIRE(rf.auto_limit());
        REQUIRE(rf.pulse_protocol());
        REQUIRE(rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0xbeu);
        REQUIRE(rf.limit() == 0x2beu);
        REQUIRE(rf.dc_coding());
        
    }

    SECTION("write fields - read raw")
    {
        HicannIfConfig rf {false, false, false, false, false, false, false, false, 0, 0, false};

        
        
        rf.start_link(false);
        rf.loopback_enable(false);
        rf.auto_init(false);
        rf.init_master(false);
        rf.use_timestamp(false);
        rf.auto_limit(false);
        rf.pulse_protocol(false);
        rf.config_protocol(false);
        rf.heap_mode(0x0);
        rf.limit(0x0);
        rf.dc_coding(false);
        REQUIRE((rf.raw & 0xfffffffu) == 0x0);
        
        rf.start_link(true);
        rf.loopback_enable(true);
        rf.auto_init(true);
        rf.init_master(true);
        rf.use_timestamp(true);
        rf.auto_limit(true);
        rf.pulse_protocol(true);
        rf.config_protocol(true);
        rf.heap_mode(0xff);
        rf.limit(0x7ff);
        rf.dc_coding(true);
        REQUIRE((rf.raw & 0xfffffffu) == 0xfffffff);
        
        rf.start_link(false);
        rf.loopback_enable(true);
        rf.auto_init(false);
        rf.init_master(true);
        rf.use_timestamp(false);
        rf.auto_limit(true);
        rf.pulse_protocol(false);
        rf.config_protocol(true);
        rf.heap_mode(0xaa);
        rf.limit(0x2aa);
        rf.dc_coding(true);
        REQUIRE((rf.raw & 0xfffffffu) == 0xaaaaaaa);
        
        rf.start_link(true);
        rf.loopback_enable(false);
        rf.auto_init(true);
        rf.init_master(false);
        rf.use_timestamp(true);
        rf.auto_limit(false);
        rf.pulse_protocol(true);
        rf.config_protocol(false);
        rf.heap_mode(0x55);
        rf.limit(0x555);
        rf.dc_coding(false);
        REQUIRE((rf.raw & 0xfffffffu) == 0x5555555);
        
        rf.start_link(true);
        rf.loopback_enable(true);
        rf.auto_init(true);
        rf.init_master(true);
        rf.use_timestamp(false);
        rf.auto_limit(true);
        rf.pulse_protocol(true);
        rf.config_protocol(true);
        rf.heap_mode(0xbe);
        rf.limit(0x2be);
        rf.dc_coding(true);
        REQUIRE((rf.raw & 0xfffffffu) == 0xabebeef);
    }
}

TEST_CASE("Definition 'HicannIfControls'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfControls rf {false, false, false, false, false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.tx_hicann_pulse_enable());
        REQUIRE(!rf.tx_hicann_config_enable());
        REQUIRE(!rf.routing_data_enable());
        REQUIRE(!rf.channel_reset());
        REQUIRE(!rf.crc_count_reset());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.tx_hicann_pulse_enable());
        REQUIRE(rf.tx_hicann_config_enable());
        REQUIRE(rf.routing_data_enable());
        REQUIRE(rf.channel_reset());
        REQUIRE(rf.crc_count_reset());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.tx_hicann_pulse_enable());
        REQUIRE(rf.tx_hicann_config_enable());
        REQUIRE(!rf.routing_data_enable());
        REQUIRE(rf.channel_reset());
        REQUIRE(!rf.crc_count_reset());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.tx_hicann_pulse_enable());
        REQUIRE(!rf.tx_hicann_config_enable());
        REQUIRE(rf.routing_data_enable());
        REQUIRE(!rf.channel_reset());
        REQUIRE(rf.crc_count_reset());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.tx_hicann_pulse_enable());
        REQUIRE(rf.tx_hicann_config_enable());
        REQUIRE(rf.routing_data_enable());
        REQUIRE(rf.channel_reset());
        REQUIRE(!rf.crc_count_reset());
        
    }

    SECTION("write fields - read raw")
    {
        HicannIfControls rf {false, false, false, false, false};

        
        
        rf.tx_hicann_pulse_enable(false);
        rf.tx_hicann_config_enable(false);
        rf.routing_data_enable(false);
        rf.channel_reset(false);
        rf.crc_count_reset(false);
        REQUIRE((rf.raw & 0x1fu) == 0x0);
        
        rf.tx_hicann_pulse_enable(true);
        rf.tx_hicann_config_enable(true);
        rf.routing_data_enable(true);
        rf.channel_reset(true);
        rf.crc_count_reset(true);
        REQUIRE((rf.raw & 0x1fu) == 0x1f);
        
        rf.tx_hicann_pulse_enable(false);
        rf.tx_hicann_config_enable(true);
        rf.routing_data_enable(false);
        rf.channel_reset(true);
        rf.crc_count_reset(false);
        REQUIRE((rf.raw & 0x1fu) == 0xa);
        
        rf.tx_hicann_pulse_enable(true);
        rf.tx_hicann_config_enable(false);
        rf.routing_data_enable(true);
        rf.channel_reset(false);
        rf.crc_count_reset(true);
        REQUIRE((rf.raw & 0x1fu) == 0x15);
        
        rf.tx_hicann_pulse_enable(true);
        rf.tx_hicann_config_enable(true);
        rf.routing_data_enable(true);
        rf.channel_reset(true);
        rf.crc_count_reset(false);
        REQUIRE((rf.raw & 0x1fu) == 0xf);
    }
}

TEST_CASE("Definition 'HicannPacketGen'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannPacketGen rf {0, false, false};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.count() == 0x0u);
        REQUIRE(!rf.error());
        REQUIRE(!rf.enable());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.count() == 0x1ffffffu);
        REQUIRE(rf.error());
        REQUIRE(rf.enable());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.count() == 0xaaaaaau);
        REQUIRE(rf.error());
        REQUIRE(!rf.enable());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.count() == 0x1555555u);
        REQUIRE(!rf.error());
        REQUIRE(rf.enable());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.count() == 0xbebeefu);
        REQUIRE(rf.error());
        REQUIRE(!rf.enable());
        
    }

    SECTION("write fields - read raw")
    {
        HicannPacketGen rf {0, false, false};

        
        
        rf.count(0x0);
        rf.error(false);
        rf.enable(false);
        REQUIRE((rf.raw & 0x7ffffffu) == 0x0);
        
        rf.count(0x1ffffff);
        rf.error(true);
        rf.enable(true);
        REQUIRE((rf.raw & 0x7ffffffu) == 0x7ffffff);
        
        rf.count(0xaaaaaa);
        rf.error(true);
        rf.enable(false);
        REQUIRE((rf.raw & 0x7ffffffu) == 0x2aaaaaa);
        
        rf.count(0x1555555);
        rf.error(false);
        rf.enable(true);
        REQUIRE((rf.raw & 0x7ffffffu) == 0x5555555);
        
        rf.count(0xbebeef);
        rf.error(true);
        rf.enable(false);
        REQUIRE((rf.raw & 0x7ffffffu) == 0x2bebeef);
    }
}

TEST_CASE("Definition 'HicannChannel'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannChannel rf {0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.number() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.number() == 0x7u);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.number() == 0x2u);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.number() == 0x5u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.number() == 0x7u);
        
    }

    SECTION("write fields - read raw")
    {
        HicannChannel rf {0};

        
        
        rf.number(0x0);
        REQUIRE((rf.raw & 0x7u) == 0x0);
        
        rf.number(0x7);
        REQUIRE((rf.raw & 0x7u) == 0x7);
        
        rf.number(0x2);
        REQUIRE((rf.raw & 0x7u) == 0x2);
        
        rf.number(0x5);
        REQUIRE((rf.raw & 0x7u) == 0x5);
        
        rf.number(0x7);
        REQUIRE((rf.raw & 0x7u) == 0x7);
    }
}

TEST_CASE("Definition 'ArqTimings'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        ArqTimings rf {0, 0, 0, false};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.master_timeout() == 0x0u);
        REQUIRE(rf.target_timeout() == 0x0u);
        REQUIRE(rf.arbiter_delay() == 0x0u);
        REQUIRE(!rf.bit());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.master_timeout() == 0x3ffu);
        REQUIRE(rf.target_timeout() == 0x3ffu);
        REQUIRE(rf.arbiter_delay() == 0x1fu);
        REQUIRE(rf.bit());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.master_timeout() == 0x2aau);
        REQUIRE(rf.target_timeout() == 0x2aau);
        REQUIRE(rf.arbiter_delay() == 0xau);
        REQUIRE(rf.bit());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.master_timeout() == 0x155u);
        REQUIRE(rf.target_timeout() == 0x155u);
        REQUIRE(rf.arbiter_delay() == 0x15u);
        REQUIRE(!rf.bit());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.master_timeout() == 0x2efu);
        REQUIRE(rf.target_timeout() == 0x3afu);
        REQUIRE(rf.arbiter_delay() == 0xbu);
        REQUIRE(rf.bit());
        
    }

    SECTION("write fields - read raw")
    {
        ArqTimings rf {0, 0, 0, false};

        
        
        rf.master_timeout(0x0);
        rf.target_timeout(0x0);
        rf.arbiter_delay(0x0);
        rf.bit(false);
        REQUIRE((rf.raw & 0x3ffffffu) == 0x0);
        
        rf.master_timeout(0x3ff);
        rf.target_timeout(0x3ff);
        rf.arbiter_delay(0x1f);
        rf.bit(true);
        REQUIRE((rf.raw & 0x3ffffffu) == 0x3ffffff);
        
        rf.master_timeout(0x2aa);
        rf.target_timeout(0x2aa);
        rf.arbiter_delay(0xa);
        rf.bit(true);
        REQUIRE((rf.raw & 0x3ffffffu) == 0x2aaaaaa);
        
        rf.master_timeout(0x155);
        rf.target_timeout(0x155);
        rf.arbiter_delay(0x15);
        rf.bit(false);
        REQUIRE((rf.raw & 0x3ffffffu) == 0x1555555);
        
        rf.master_timeout(0x2ef);
        rf.target_timeout(0x3af);
        rf.arbiter_delay(0xb);
        rf.bit(true);
        REQUIRE((rf.raw & 0x3ffffffu) == 0x2bebeef);
    }
}

TEST_CASE("Definition 'TestControlEnable'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TestControlEnable rf {false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.enable());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.enable());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.enable());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.enable());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.enable());
        
    }

    SECTION("write fields - read raw")
    {
        TestControlEnable rf {false};

        
        
        rf.enable(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.enable(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.enable(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.enable(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.enable(true);
        REQUIRE((rf.raw & 0x1u) == 1);
    }
}

TEST_CASE("Definition 'TestControlConfig'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TestControlConfig rf {0, 0, false};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.quad_words() == 0x0u);
        REQUIRE(rf.pause_time() == 0x0u);
        REQUIRE(!rf.count_up());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.quad_words() == 0xffu);
        REQUIRE(rf.pause_time() == 0xffu);
        REQUIRE(rf.count_up());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.quad_words() == 0xaau);
        REQUIRE(rf.pause_time() == 0xaau);
        REQUIRE(!rf.count_up());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.quad_words() == 0x55u);
        REQUIRE(rf.pause_time() == 0x55u);
        REQUIRE(rf.count_up());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.quad_words() == 0xefu);
        REQUIRE(rf.pause_time() == 0xbeu);
        REQUIRE(!rf.count_up());
        
    }

    SECTION("write fields - read raw")
    {
        TestControlConfig rf {0, 0, false};

        
        
        rf.quad_words(0x0);
        rf.pause_time(0x0);
        rf.count_up(false);
        REQUIRE((rf.raw & 0x1ffffu) == 0x0);
        
        rf.quad_words(0xff);
        rf.pause_time(0xff);
        rf.count_up(true);
        REQUIRE((rf.raw & 0x1ffffu) == 0x1ffff);
        
        rf.quad_words(0xaa);
        rf.pause_time(0xaa);
        rf.count_up(false);
        REQUIRE((rf.raw & 0x1ffffu) == 0xaaaa);
        
        rf.quad_words(0x55);
        rf.pause_time(0x55);
        rf.count_up(true);
        REQUIRE((rf.raw & 0x1ffffu) == 0x15555);
        
        rf.quad_words(0xef);
        rf.pause_time(0xbe);
        rf.count_up(false);
        REQUIRE((rf.raw & 0x1ffffu) == 0xbeef);
    }
}

TEST_CASE("Definition 'TestControlStart'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TestControlStart rf {false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.start());
        
    }

    SECTION("write fields - read raw")
    {
        TestControlStart rf {false};

        
        
        rf.start(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.start(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.start(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.start(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.start(true);
        REQUIRE((rf.raw & 0x1u) == 1);
    }
}

TEST_CASE("Definition 'TestControlType'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TestControlType rf {TestControlType::Type(0)};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.type() == TestControlType::Type(0x0));
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.type() == TestControlType::Type(0xffff));
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.type() == TestControlType::Type(0xaaaa));
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.type() == TestControlType::Type(0x5555));
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.type() == TestControlType::Type(0xbeef));
        
    }

    SECTION("write fields - read raw")
    {
        TestControlType rf {TestControlType::Type(0)};

        
        
        rf.type(TestControlType::Type(0x0));
        REQUIRE((rf.raw & 0xffffu) == 0x0);
        
        rf.type(TestControlType::Type(0xffff));
        REQUIRE((rf.raw & 0xffffu) == 0xffff);
        
        rf.type(TestControlType::Type(0xaaaa));
        REQUIRE((rf.raw & 0xffffu) == 0xaaaa);
        
        rf.type(TestControlType::Type(0x5555));
        REQUIRE((rf.raw & 0xffffu) == 0x5555);
        
        rf.type(TestControlType::Type(0xbeef));
        REQUIRE((rf.raw & 0xffffu) == 0xbeef);
    }
}

TEST_CASE("Definition 'TraceBufferSize'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferSize rf {0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.data() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.data() == 0xffffffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.data() == 0xaaaaaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.data() == 0x55555555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.data() == 0xbabebeefu);
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferSize rf {0};

        
        
        rf.data(0x0);
        REQUIRE((rf.raw & 0xffffffffu) == 0x0);
        
        rf.data(0xffffffff);
        REQUIRE((rf.raw & 0xffffffffu) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);
        REQUIRE((rf.raw & 0xffffffffu) == 0xaaaaaaaa);
        
        rf.data(0x55555555);
        REQUIRE((rf.raw & 0xffffffffu) == 0x55555555);
        
        rf.data(0xbabebeef);
        REQUIRE((rf.raw & 0xffffffffu) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'TraceBufferFullThreshold'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferFullThreshold rf {0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.data() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.data() == 0xffffffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.data() == 0xaaaaaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.data() == 0x55555555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.data() == 0xbabebeefu);
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferFullThreshold rf {0};

        
        
        rf.data(0x0);
        REQUIRE((rf.raw & 0xffffffffu) == 0x0);
        
        rf.data(0xffffffff);
        REQUIRE((rf.raw & 0xffffffffu) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);
        REQUIRE((rf.raw & 0xffffffffu) == 0xaaaaaaaa);
        
        rf.data(0x55555555);
        REQUIRE((rf.raw & 0xffffffffu) == 0x55555555);
        
        rf.data(0xbabebeef);
        REQUIRE((rf.raw & 0xffffffffu) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'TraceBufferCounter'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferCounter rf {0, 0, 0, 0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.start_address() == 0x0u);
        REQUIRE(rf.size() == 0x0u);
        REQUIRE(rf.threshold() == 0x0u);
        REQUIRE(rf.wraps() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.start_address() == 0xffffu);
        REQUIRE(rf.size() == 0xffffu);
        REQUIRE(rf.threshold() == 0xffffu);
        REQUIRE(rf.wraps() == 0xffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.start_address() == 0xaaaau);
        REQUIRE(rf.size() == 0xaaaau);
        REQUIRE(rf.threshold() == 0xaaaau);
        REQUIRE(rf.wraps() == 0xaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.start_address() == 0x5555u);
        REQUIRE(rf.size() == 0x5555u);
        REQUIRE(rf.threshold() == 0x5555u);
        REQUIRE(rf.wraps() == 0x5555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.start_address() == 0xbeefu);
        REQUIRE(rf.size() == 0xbabeu);
        REQUIRE(rf.threshold() == 0xdeadu);
        REQUIRE(rf.wraps() == 0xcafeu);
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferCounter rf {0, 0, 0, 0};

        
        
        rf.start_address(0x0);
        rf.size(0x0);
        rf.threshold(0x0);
        rf.wraps(0x0);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0x0);
        
        rf.start_address(0xffff);
        rf.size(0xffff);
        rf.threshold(0xffff);
        rf.wraps(0xffff);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xffffffffffffffff);
        
        rf.start_address(0xaaaa);
        rf.size(0xaaaa);
        rf.threshold(0xaaaa);
        rf.wraps(0xaaaa);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xaaaaaaaaaaaaaaaa);
        
        rf.start_address(0x5555);
        rf.size(0x5555);
        rf.threshold(0x5555);
        rf.wraps(0x5555);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0x5555555555555555);
        
        rf.start_address(0xbeef);
        rf.size(0xbabe);
        rf.threshold(0xdead);
        rf.wraps(0xcafe);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xcafedeadbabebeef);
    }
}

TEST_CASE("Definition 'TraceBufferCounterReset'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferCounterReset rf {false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.reset());
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferCounterReset rf {false};

        
        
        rf.reset(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.reset(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.reset(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.reset(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.reset(true);
        REQUIRE((rf.raw & 0x1u) == 1);
    }
}

TEST_CASE("Definition 'TraceBufferFreeSpace'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferFreeSpace rf {0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.data() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.data() == 0xffffffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.data() == 0xaaaaaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.data() == 0x55555555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.data() == 0xbabebeefu);
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferFreeSpace rf {0};

        
        
        rf.data(0x0);
        REQUIRE((rf.raw & 0xffffffffu) == 0x0);
        
        rf.data(0xffffffff);
        REQUIRE((rf.raw & 0xffffffffu) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);
        REQUIRE((rf.raw & 0xffffffffu) == 0xaaaaaaaa);
        
        rf.data(0x55555555);
        REQUIRE((rf.raw & 0xffffffffu) == 0x55555555);
        
        rf.data(0xbabebeef);
        REQUIRE((rf.raw & 0xffffffffu) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'TraceBufferInit'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferInit rf {false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.start());
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferInit rf {false};

        
        
        rf.start(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.start(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.start(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.start(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.start(true);
        REQUIRE((rf.raw & 0x1u) == 1);
    }
}

TEST_CASE("Definition 'HicannBufferSize'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferSize rf {0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.data() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.data() == 0xffffffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.data() == 0xaaaaaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.data() == 0x55555555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.data() == 0xbabebeefu);
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferSize rf {0};

        
        
        rf.data(0x0);
        REQUIRE((rf.raw & 0xffffffffu) == 0x0);
        
        rf.data(0xffffffff);
        REQUIRE((rf.raw & 0xffffffffu) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);
        REQUIRE((rf.raw & 0xffffffffu) == 0xaaaaaaaa);
        
        rf.data(0x55555555);
        REQUIRE((rf.raw & 0xffffffffu) == 0x55555555);
        
        rf.data(0xbabebeef);
        REQUIRE((rf.raw & 0xffffffffu) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'HicannBufferFullThreshold'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferFullThreshold rf {0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.data() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.data() == 0xffffffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.data() == 0xaaaaaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.data() == 0x55555555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.data() == 0xbabebeefu);
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferFullThreshold rf {0};

        
        
        rf.data(0x0);
        REQUIRE((rf.raw & 0xffffffffu) == 0x0);
        
        rf.data(0xffffffff);
        REQUIRE((rf.raw & 0xffffffffu) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);
        REQUIRE((rf.raw & 0xffffffffu) == 0xaaaaaaaa);
        
        rf.data(0x55555555);
        REQUIRE((rf.raw & 0xffffffffu) == 0x55555555);
        
        rf.data(0xbabebeef);
        REQUIRE((rf.raw & 0xffffffffu) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'HicannBufferCounter'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferCounter rf {0, 0, 0, 0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.start_address() == 0x0u);
        REQUIRE(rf.size() == 0x0u);
        REQUIRE(rf.threshold() == 0x0u);
        REQUIRE(rf.wraps() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.start_address() == 0xffffu);
        REQUIRE(rf.size() == 0xffffu);
        REQUIRE(rf.threshold() == 0xffffu);
        REQUIRE(rf.wraps() == 0xffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.start_address() == 0xaaaau);
        REQUIRE(rf.size() == 0xaaaau);
        REQUIRE(rf.threshold() == 0xaaaau);
        REQUIRE(rf.wraps() == 0xaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.start_address() == 0x5555u);
        REQUIRE(rf.size() == 0x5555u);
        REQUIRE(rf.threshold() == 0x5555u);
        REQUIRE(rf.wraps() == 0x5555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.start_address() == 0xbeefu);
        REQUIRE(rf.size() == 0xbabeu);
        REQUIRE(rf.threshold() == 0xdeadu);
        REQUIRE(rf.wraps() == 0xcafeu);
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferCounter rf {0, 0, 0, 0};

        
        
        rf.start_address(0x0);
        rf.size(0x0);
        rf.threshold(0x0);
        rf.wraps(0x0);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0x0);
        
        rf.start_address(0xffff);
        rf.size(0xffff);
        rf.threshold(0xffff);
        rf.wraps(0xffff);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xffffffffffffffff);
        
        rf.start_address(0xaaaa);
        rf.size(0xaaaa);
        rf.threshold(0xaaaa);
        rf.wraps(0xaaaa);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xaaaaaaaaaaaaaaaa);
        
        rf.start_address(0x5555);
        rf.size(0x5555);
        rf.threshold(0x5555);
        rf.wraps(0x5555);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0x5555555555555555);
        
        rf.start_address(0xbeef);
        rf.size(0xbabe);
        rf.threshold(0xdead);
        rf.wraps(0xcafe);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xcafedeadbabebeef);
    }
}

TEST_CASE("Definition 'HicannBufferCounterReset'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferCounterReset rf {false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.reset());
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferCounterReset rf {false};

        
        
        rf.reset(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.reset(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.reset(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.reset(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.reset(true);
        REQUIRE((rf.raw & 0x1u) == 1);
    }
}

TEST_CASE("Definition 'HicannBufferFreeSpace'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferFreeSpace rf {0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.data() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.data() == 0xffffffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.data() == 0xaaaaaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.data() == 0x55555555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.data() == 0xbabebeefu);
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferFreeSpace rf {0};

        
        
        rf.data(0x0);
        REQUIRE((rf.raw & 0xffffffffu) == 0x0);
        
        rf.data(0xffffffff);
        REQUIRE((rf.raw & 0xffffffffu) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);
        REQUIRE((rf.raw & 0xffffffffu) == 0xaaaaaaaa);
        
        rf.data(0x55555555);
        REQUIRE((rf.raw & 0xffffffffu) == 0x55555555);
        
        rf.data(0xbabebeef);
        REQUIRE((rf.raw & 0xffffffffu) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'HicannBufferInit'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferInit rf {false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.start());
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferInit rf {false};

        
        
        rf.start(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.start(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.start(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.start(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.start(true);
        REQUIRE((rf.raw & 0x1u) == 1);
    }
}

TEST_CASE("Definition 'CounterReset'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        CounterReset rf {false};

        
        rf.raw = 0x0u;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.reset());
        
    }

    SECTION("write fields - read raw")
    {
        CounterReset rf {false};

        
        
        rf.reset(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.reset(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.reset(false);
        REQUIRE((rf.raw & 0x1u) == 0);
        
        rf.reset(true);
        REQUIRE((rf.raw & 0x1u) == 1);
        
        rf.reset(true);
        REQUIRE((rf.raw & 0x1u) == 1);
    }
}

TEST_CASE("Definition 'HostEndpoint'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HostEndpoint rf {0, 0, 0, 0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.node_id() == 0x0u);
        REQUIRE(rf.protection_domain() == 0x0u);
        REQUIRE(rf.vpid() == 0x0u);
        REQUIRE(rf.mode() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.node_id() == 0xffffu);
        REQUIRE(rf.protection_domain() == 0xffffu);
        REQUIRE(rf.vpid() == 0x3ffu);
        REQUIRE(rf.mode() == 0x3fu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.node_id() == 0xaaaau);
        REQUIRE(rf.protection_domain() == 0xaaaau);
        REQUIRE(rf.vpid() == 0x2aau);
        REQUIRE(rf.mode() == 0x2au);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.node_id() == 0x5555u);
        REQUIRE(rf.protection_domain() == 0x5555u);
        REQUIRE(rf.vpid() == 0x155u);
        REQUIRE(rf.mode() == 0x15u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.node_id() == 0xbeefu);
        REQUIRE(rf.protection_domain() == 0xbabeu);
        REQUIRE(rf.vpid() == 0x2adu);
        REQUIRE(rf.mode() == 0x37u);
        
    }

    SECTION("write fields - read raw")
    {
        HostEndpoint rf {0, 0, 0, 0};

        
        
        rf.node_id(0x0);
        rf.protection_domain(0x0);
        rf.vpid(0x0);
        rf.mode(0x0);
        REQUIRE((rf.raw & 0xffffffffffffu) == 0x0);
        
        rf.node_id(0xffff);
        rf.protection_domain(0xffff);
        rf.vpid(0x3ff);
        rf.mode(0x3f);
        REQUIRE((rf.raw & 0xffffffffffffu) == 0xffffffffffff);
        
        rf.node_id(0xaaaa);
        rf.protection_domain(0xaaaa);
        rf.vpid(0x2aa);
        rf.mode(0x2a);
        REQUIRE((rf.raw & 0xffffffffffffu) == 0xaaaaaaaaaaaa);
        
        rf.node_id(0x5555);
        rf.protection_domain(0x5555);
        rf.vpid(0x155);
        rf.mode(0x15);
        REQUIRE((rf.raw & 0xffffffffffffu) == 0x555555555555);
        
        rf.node_id(0xbeef);
        rf.protection_domain(0xbabe);
        rf.vpid(0x2ad);
        rf.mode(0x37);
        REQUIRE((rf.raw & 0xffffffffffffu) == 0xdeadbabebeef);
    }
}

TEST_CASE("Definition 'TraceNotificationBehaviour'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceNotificationBehaviour rf {0, 0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.timeout() == 0x0u);
        REQUIRE(rf.frequency() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.timeout() == 0xffffffffu);
        REQUIRE(rf.frequency() == 0xffffffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.timeout() == 0xaaaaaaaau);
        REQUIRE(rf.frequency() == 0xaaaaaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.timeout() == 0x55555555u);
        REQUIRE(rf.frequency() == 0x55555555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.timeout() == 0xbabebeefu);
        REQUIRE(rf.frequency() == 0xcafedeadu);
        
    }

    SECTION("write fields - read raw")
    {
        TraceNotificationBehaviour rf {0, 0};

        
        
        rf.timeout(0x0);
        rf.frequency(0x0);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0x0);
        
        rf.timeout(0xffffffff);
        rf.frequency(0xffffffff);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xffffffffffffffff);
        
        rf.timeout(0xaaaaaaaa);
        rf.frequency(0xaaaaaaaa);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xaaaaaaaaaaaaaaaa);
        
        rf.timeout(0x55555555);
        rf.frequency(0x55555555);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0x5555555555555555);
        
        rf.timeout(0xbabebeef);
        rf.frequency(0xcafedead);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xcafedeadbabebeef);
    }
}

TEST_CASE("Definition 'HicannNotificationBehaviour'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannNotificationBehaviour rf {0, 0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.timeout() == 0x0u);
        REQUIRE(rf.frequency() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.timeout() == 0xffffffffu);
        REQUIRE(rf.frequency() == 0xffffffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.timeout() == 0xaaaaaaaau);
        REQUIRE(rf.frequency() == 0xaaaaaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.timeout() == 0x55555555u);
        REQUIRE(rf.frequency() == 0x55555555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.timeout() == 0xbabebeefu);
        REQUIRE(rf.frequency() == 0xcafedeadu);
        
    }

    SECTION("write fields - read raw")
    {
        HicannNotificationBehaviour rf {0, 0};

        
        
        rf.timeout(0x0);
        rf.frequency(0x0);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0x0);
        
        rf.timeout(0xffffffff);
        rf.frequency(0xffffffff);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xffffffffffffffff);
        
        rf.timeout(0xaaaaaaaa);
        rf.frequency(0xaaaaaaaa);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xaaaaaaaaaaaaaaaa);
        
        rf.timeout(0x55555555);
        rf.frequency(0x55555555);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0x5555555555555555);
        
        rf.timeout(0xbabebeef);
        rf.frequency(0xcafedead);
        REQUIRE((rf.raw & 0xffffffffffffffffu) == 0xcafedeadbabebeef);
    }
}

TEST_CASE("Definition 'Info'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        Info rf {0, 0};

        
        rf.raw = 0x0u;

        
        REQUIRE(rf.guid() == 0x0u);
        REQUIRE(rf.node_id() == 0x0u);
        
        rf.raw = 0xffffffffffffffffu;

        
        REQUIRE(rf.guid() == 0xffffffu);
        REQUIRE(rf.node_id() == 0xffffu);
        
        rf.raw = 0xaaaaaaaaaaaaaaaau;

        
        REQUIRE(rf.guid() == 0xaaaaaau);
        REQUIRE(rf.node_id() == 0xaaaau);
        
        rf.raw = 0x5555555555555555u;

        
        REQUIRE(rf.guid() == 0x555555u);
        REQUIRE(rf.node_id() == 0x5555u);
        
        rf.raw = 0xcafedeadbabebeefu;

        
        REQUIRE(rf.guid() == 0xbebeefu);
        REQUIRE(rf.node_id() == 0xadbau);
        
    }

    SECTION("write fields - read raw")
    {
        Info rf {0, 0};

        
        
        rf.guid(0x0);
        rf.node_id(0x0);
        REQUIRE((rf.raw & 0xffffffffffu) == 0x0);
        
        rf.guid(0xffffff);
        rf.node_id(0xffff);
        REQUIRE((rf.raw & 0xffffffffffu) == 0xffffffffff);
        
        rf.guid(0xaaaaaa);
        rf.node_id(0xaaaa);
        REQUIRE((rf.raw & 0xffffffffffu) == 0xaaaaaaaaaa);
        
        rf.guid(0x555555);
        rf.node_id(0x5555);
        REQUIRE((rf.raw & 0xffffffffffu) == 0x5555555555);
        
        rf.guid(0xbebeef);
        rf.node_id(0xadba);
        REQUIRE((rf.raw & 0xffffffffffu) == 0xadbabebeef);
    }
}

