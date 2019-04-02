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

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.core());
        REQUIRE(!rf.hicann());
        REQUIRE(!rf.arq());
        REQUIRE(!rf.pulse_mem());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.core());
        REQUIRE(rf.hicann());
        REQUIRE(rf.arq());
        REQUIRE(rf.pulse_mem());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.core());
        REQUIRE(rf.hicann());
        REQUIRE(!rf.arq());
        REQUIRE(rf.pulse_mem());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.core());
        REQUIRE(!rf.hicann());
        REQUIRE(rf.arq());
        REQUIRE(!rf.pulse_mem());
        
        rf.raw = 0xcafedeadbabebeef;

        
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

        REQUIRE((rf.raw & 0xf) == 0x0);
        
        rf.core(true);
        rf.hicann(true);
        rf.arq(true);
        rf.pulse_mem(true);

        REQUIRE((rf.raw & 0xf) == 0xf);
        
        rf.core(false);
        rf.hicann(true);
        rf.arq(false);
        rf.pulse_mem(true);

        REQUIRE((rf.raw & 0xf) == 0xa);
        
        rf.core(true);
        rf.hicann(false);
        rf.arq(true);
        rf.pulse_mem(false);

        REQUIRE((rf.raw & 0xf) == 0x5);
        
        rf.core(true);
        rf.hicann(true);
        rf.arq(true);
        rf.pulse_mem(true);

        REQUIRE((rf.raw & 0xf) == 0xf);
    }
}

TEST_CASE("Definition 'JtagCmd'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        JtagCmd rf {JtagCmd::Type(0), 0, false, false};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x0));
        REQUIRE(rf.length() == 0x0);
        REQUIRE(!rf.pause());
        REQUIRE(!rf.execute());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x7));
        REQUIRE(rf.length() == 0x3ff);
        REQUIRE(rf.pause());
        REQUIRE(rf.execute());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x2));
        REQUIRE(rf.length() == 0x155);
        REQUIRE(rf.pause());
        REQUIRE(!rf.execute());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x5));
        REQUIRE(rf.length() == 0x2aa);
        REQUIRE(!rf.pause());
        REQUIRE(rf.execute());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.type() == JtagCmd::Type(0x7));
        REQUIRE(rf.length() == 0x3dd);
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

        REQUIRE((rf.raw & 0x7fff) == 0x0);
        
        rf.type(JtagCmd::Type(0x7));
        rf.length(0x3ff);
        rf.pause(true);
        rf.execute(true);

        REQUIRE((rf.raw & 0x7fff) == 0x7fff);
        
        rf.type(JtagCmd::Type(0x2));
        rf.length(0x155);
        rf.pause(true);
        rf.execute(false);

        REQUIRE((rf.raw & 0x7fff) == 0x2aaa);
        
        rf.type(JtagCmd::Type(0x5));
        rf.length(0x2aa);
        rf.pause(false);
        rf.execute(true);

        REQUIRE((rf.raw & 0x7fff) == 0x5555);
        
        rf.type(JtagCmd::Type(0x7));
        rf.length(0x3dd);
        rf.pause(true);
        rf.execute(false);

        REQUIRE((rf.raw & 0x7fff) == 0x3eef);
    }
}

TEST_CASE("Definition 'JtagStatus'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        JtagStatus rf {false, false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.clock_enabled());
        REQUIRE(!rf.paused());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.clock_enabled());
        REQUIRE(rf.paused());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.clock_enabled());
        REQUIRE(rf.paused());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.clock_enabled());
        REQUIRE(!rf.paused());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.clock_enabled());
        REQUIRE(rf.paused());
        
    }

    SECTION("write fields - read raw")
    {
        JtagStatus rf {false, false};

        
        
        rf.clock_enabled(false);
        rf.paused(false);

        REQUIRE((rf.raw & 0x3) == 0x0);
        
        rf.clock_enabled(true);
        rf.paused(true);

        REQUIRE((rf.raw & 0x3) == 0x3);
        
        rf.clock_enabled(false);
        rf.paused(true);

        REQUIRE((rf.raw & 0x3) == 0x2);
        
        rf.clock_enabled(true);
        rf.paused(false);

        REQUIRE((rf.raw & 0x3) == 0x1);
        
        rf.clock_enabled(true);
        rf.paused(true);

        REQUIRE((rf.raw & 0x3) == 0x3);
    }
}

TEST_CASE("Definition 'HicannIfState'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfState rf {0, 0, 0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.channel_status() == 0x0);
        REQUIRE(rf.crc_count() == 0x0);
        REQUIRE(rf.systime() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.channel_status() == 0xff);
        REQUIRE(rf.crc_count() == 0xff);
        REQUIRE(rf.systime() == 0x3fff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.channel_status() == 0xaa);
        REQUIRE(rf.crc_count() == 0xaa);
        REQUIRE(rf.systime() == 0x2aaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.channel_status() == 0x55);
        REQUIRE(rf.crc_count() == 0x55);
        REQUIRE(rf.systime() == 0x1555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.channel_status() == 0xef);
        REQUIRE(rf.crc_count() == 0xbe);
        REQUIRE(rf.systime() == 0x3abe);
        
    }

    SECTION("write fields - read raw")
    {
        HicannIfState rf {0, 0, 0};

        
        
        rf.channel_status(0x0);
        rf.crc_count(0x0);
        rf.systime(0x0);

        REQUIRE((rf.raw & 0x3fffffff) == 0x0);
        
        rf.channel_status(0xff);
        rf.crc_count(0xff);
        rf.systime(0x3fff);

        REQUIRE((rf.raw & 0x3fffffff) == 0x3fffffff);
        
        rf.channel_status(0xaa);
        rf.crc_count(0xaa);
        rf.systime(0x2aaa);

        REQUIRE((rf.raw & 0x3fffffff) == 0x2aaaaaaa);
        
        rf.channel_status(0x55);
        rf.crc_count(0x55);
        rf.systime(0x1555);

        REQUIRE((rf.raw & 0x3fffffff) == 0x15555555);
        
        rf.channel_status(0xef);
        rf.crc_count(0xbe);
        rf.systime(0x3abe);

        REQUIRE((rf.raw & 0x3fffffff) == 0x3abebeef);
    }
}

TEST_CASE("Definition 'HicannIfRxPulse'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfRxPulse rf {0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.data() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.data() == 0xffffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.data() == 0xaaaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.data() == 0x555555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.data() == 0xbebeef);
        
    }

    SECTION("write fields - read raw")
    {
        HicannIfRxPulse rf {0};

        
        
        rf.data(0x0);

        REQUIRE((rf.raw & 0xffffff) == 0x0);
        
        rf.data(0xffffff);

        REQUIRE((rf.raw & 0xffffff) == 0xffffff);
        
        rf.data(0xaaaaaa);

        REQUIRE((rf.raw & 0xffffff) == 0xaaaaaa);
        
        rf.data(0x555555);

        REQUIRE((rf.raw & 0xffffff) == 0x555555);
        
        rf.data(0xbebeef);

        REQUIRE((rf.raw & 0xffffff) == 0xbebeef);
    }
}

TEST_CASE("Definition 'HicannIfConfig'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfConfig rf {false, false, false, false, false, false, false, false, 0, 0, false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.start_link());
        REQUIRE(!rf.loopback_enable());
        REQUIRE(!rf.auto_init());
        REQUIRE(!rf.init_master());
        REQUIRE(!rf.use_timestamp());
        REQUIRE(!rf.auto_limit());
        REQUIRE(!rf.pulse_protocol());
        REQUIRE(!rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0x0);
        REQUIRE(rf.limit() == 0x0);
        REQUIRE(!rf.dc_coding());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.start_link());
        REQUIRE(rf.loopback_enable());
        REQUIRE(rf.auto_init());
        REQUIRE(rf.init_master());
        REQUIRE(rf.use_timestamp());
        REQUIRE(rf.auto_limit());
        REQUIRE(rf.pulse_protocol());
        REQUIRE(rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0xff);
        REQUIRE(rf.limit() == 0x7ff);
        REQUIRE(rf.dc_coding());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.start_link());
        REQUIRE(rf.loopback_enable());
        REQUIRE(!rf.auto_init());
        REQUIRE(rf.init_master());
        REQUIRE(!rf.use_timestamp());
        REQUIRE(rf.auto_limit());
        REQUIRE(!rf.pulse_protocol());
        REQUIRE(rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0xaa);
        REQUIRE(rf.limit() == 0x2aa);
        REQUIRE(rf.dc_coding());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.start_link());
        REQUIRE(!rf.loopback_enable());
        REQUIRE(rf.auto_init());
        REQUIRE(!rf.init_master());
        REQUIRE(rf.use_timestamp());
        REQUIRE(!rf.auto_limit());
        REQUIRE(rf.pulse_protocol());
        REQUIRE(!rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0x55);
        REQUIRE(rf.limit() == 0x555);
        REQUIRE(!rf.dc_coding());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.start_link());
        REQUIRE(rf.loopback_enable());
        REQUIRE(rf.auto_init());
        REQUIRE(rf.init_master());
        REQUIRE(!rf.use_timestamp());
        REQUIRE(rf.auto_limit());
        REQUIRE(rf.pulse_protocol());
        REQUIRE(rf.config_protocol());
        REQUIRE(rf.heap_mode() == 0xbe);
        REQUIRE(rf.limit() == 0x2be);
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

        REQUIRE((rf.raw & 0xfffffff) == 0x0);
        
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

        REQUIRE((rf.raw & 0xfffffff) == 0xfffffff);
        
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

        REQUIRE((rf.raw & 0xfffffff) == 0xaaaaaaa);
        
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

        REQUIRE((rf.raw & 0xfffffff) == 0x5555555);
        
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

        REQUIRE((rf.raw & 0xfffffff) == 0xabebeef);
    }
}

TEST_CASE("Definition 'HicannIfControls'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfControls rf {false, false, false, false, false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.tx_hicann_pulse_enable());
        REQUIRE(!rf.tx_hicann_config_enable());
        REQUIRE(!rf.routing_data_enable());
        REQUIRE(!rf.channel_reset());
        REQUIRE(!rf.crc_count_reset());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.tx_hicann_pulse_enable());
        REQUIRE(rf.tx_hicann_config_enable());
        REQUIRE(rf.routing_data_enable());
        REQUIRE(rf.channel_reset());
        REQUIRE(rf.crc_count_reset());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.tx_hicann_pulse_enable());
        REQUIRE(rf.tx_hicann_config_enable());
        REQUIRE(!rf.routing_data_enable());
        REQUIRE(rf.channel_reset());
        REQUIRE(!rf.crc_count_reset());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.tx_hicann_pulse_enable());
        REQUIRE(!rf.tx_hicann_config_enable());
        REQUIRE(rf.routing_data_enable());
        REQUIRE(!rf.channel_reset());
        REQUIRE(rf.crc_count_reset());
        
        rf.raw = 0xcafedeadbabebeef;

        
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

        REQUIRE((rf.raw & 0x1f) == 0x0);
        
        rf.tx_hicann_pulse_enable(true);
        rf.tx_hicann_config_enable(true);
        rf.routing_data_enable(true);
        rf.channel_reset(true);
        rf.crc_count_reset(true);

        REQUIRE((rf.raw & 0x1f) == 0x1f);
        
        rf.tx_hicann_pulse_enable(false);
        rf.tx_hicann_config_enable(true);
        rf.routing_data_enable(false);
        rf.channel_reset(true);
        rf.crc_count_reset(false);

        REQUIRE((rf.raw & 0x1f) == 0xa);
        
        rf.tx_hicann_pulse_enable(true);
        rf.tx_hicann_config_enable(false);
        rf.routing_data_enable(true);
        rf.channel_reset(false);
        rf.crc_count_reset(true);

        REQUIRE((rf.raw & 0x1f) == 0x15);
        
        rf.tx_hicann_pulse_enable(true);
        rf.tx_hicann_config_enable(true);
        rf.routing_data_enable(true);
        rf.channel_reset(true);
        rf.crc_count_reset(false);

        REQUIRE((rf.raw & 0x1f) == 0xf);
    }
}

TEST_CASE("Definition 'HicannPacketGen'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannPacketGen rf {0, false, false};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.count() == 0x0);
        REQUIRE(!rf.error());
        REQUIRE(!rf.enable());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.count() == 0x1ffffff);
        REQUIRE(rf.error());
        REQUIRE(rf.enable());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.count() == 0xaaaaaa);
        REQUIRE(rf.error());
        REQUIRE(!rf.enable());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.count() == 0x1555555);
        REQUIRE(!rf.error());
        REQUIRE(rf.enable());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.count() == 0xbebeef);
        REQUIRE(rf.error());
        REQUIRE(!rf.enable());
        
    }

    SECTION("write fields - read raw")
    {
        HicannPacketGen rf {0, false, false};

        
        
        rf.count(0x0);
        rf.error(false);
        rf.enable(false);

        REQUIRE((rf.raw & 0x7ffffff) == 0x0);
        
        rf.count(0x1ffffff);
        rf.error(true);
        rf.enable(true);

        REQUIRE((rf.raw & 0x7ffffff) == 0x7ffffff);
        
        rf.count(0xaaaaaa);
        rf.error(true);
        rf.enable(false);

        REQUIRE((rf.raw & 0x7ffffff) == 0x2aaaaaa);
        
        rf.count(0x1555555);
        rf.error(false);
        rf.enable(true);

        REQUIRE((rf.raw & 0x7ffffff) == 0x5555555);
        
        rf.count(0xbebeef);
        rf.error(true);
        rf.enable(false);

        REQUIRE((rf.raw & 0x7ffffff) == 0x2bebeef);
    }
}

TEST_CASE("Definition 'HicannChannel'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannChannel rf {0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.number() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.number() == 0x7);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.number() == 0x2);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.number() == 0x5);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.number() == 0x7);
        
    }

    SECTION("write fields - read raw")
    {
        HicannChannel rf {0};

        
        
        rf.number(0x0);

        REQUIRE((rf.raw & 0x7) == 0x0);
        
        rf.number(0x7);

        REQUIRE((rf.raw & 0x7) == 0x7);
        
        rf.number(0x2);

        REQUIRE((rf.raw & 0x7) == 0x2);
        
        rf.number(0x5);

        REQUIRE((rf.raw & 0x7) == 0x5);
        
        rf.number(0x7);

        REQUIRE((rf.raw & 0x7) == 0x7);
    }
}

TEST_CASE("Definition 'ArqTimings'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        ArqTimings rf {0, 0, 0, false};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.master_timeout() == 0x0);
        REQUIRE(rf.target_timeout() == 0x0);
        REQUIRE(rf.arbiter_delay() == 0x0);
        REQUIRE(!rf.bit());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.master_timeout() == 0x3ff);
        REQUIRE(rf.target_timeout() == 0x3ff);
        REQUIRE(rf.arbiter_delay() == 0x1f);
        REQUIRE(rf.bit());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.master_timeout() == 0x2aa);
        REQUIRE(rf.target_timeout() == 0x2aa);
        REQUIRE(rf.arbiter_delay() == 0xa);
        REQUIRE(rf.bit());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.master_timeout() == 0x155);
        REQUIRE(rf.target_timeout() == 0x155);
        REQUIRE(rf.arbiter_delay() == 0x15);
        REQUIRE(!rf.bit());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.master_timeout() == 0x2ef);
        REQUIRE(rf.target_timeout() == 0x3af);
        REQUIRE(rf.arbiter_delay() == 0xb);
        REQUIRE(rf.bit());
        
    }

    SECTION("write fields - read raw")
    {
        ArqTimings rf {0, 0, 0, false};

        
        
        rf.master_timeout(0x0);
        rf.target_timeout(0x0);
        rf.arbiter_delay(0x0);
        rf.bit(false);

        REQUIRE((rf.raw & 0x3ffffff) == 0x0);
        
        rf.master_timeout(0x3ff);
        rf.target_timeout(0x3ff);
        rf.arbiter_delay(0x1f);
        rf.bit(true);

        REQUIRE((rf.raw & 0x3ffffff) == 0x3ffffff);
        
        rf.master_timeout(0x2aa);
        rf.target_timeout(0x2aa);
        rf.arbiter_delay(0xa);
        rf.bit(true);

        REQUIRE((rf.raw & 0x3ffffff) == 0x2aaaaaa);
        
        rf.master_timeout(0x155);
        rf.target_timeout(0x155);
        rf.arbiter_delay(0x15);
        rf.bit(false);

        REQUIRE((rf.raw & 0x3ffffff) == 0x1555555);
        
        rf.master_timeout(0x2ef);
        rf.target_timeout(0x3af);
        rf.arbiter_delay(0xb);
        rf.bit(true);

        REQUIRE((rf.raw & 0x3ffffff) == 0x2bebeef);
    }
}

TEST_CASE("Definition 'TestControlEnable'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TestControlEnable rf {false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.enable());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.enable());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.enable());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.enable());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.enable());
        
    }

    SECTION("write fields - read raw")
    {
        TestControlEnable rf {false};

        
        
        rf.enable(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.enable(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.enable(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.enable(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.enable(true);

        REQUIRE((rf.raw & 0x1) == true);
    }
}

TEST_CASE("Definition 'TestControlConfig'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TestControlConfig rf {0, 0, false};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.quad_words() == 0x0);
        REQUIRE(rf.pause_time() == 0x0);
        REQUIRE(!rf.count_up());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.quad_words() == 0xff);
        REQUIRE(rf.pause_time() == 0xff);
        REQUIRE(rf.count_up());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.quad_words() == 0xaa);
        REQUIRE(rf.pause_time() == 0xaa);
        REQUIRE(!rf.count_up());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.quad_words() == 0x55);
        REQUIRE(rf.pause_time() == 0x55);
        REQUIRE(rf.count_up());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.quad_words() == 0xef);
        REQUIRE(rf.pause_time() == 0xbe);
        REQUIRE(!rf.count_up());
        
    }

    SECTION("write fields - read raw")
    {
        TestControlConfig rf {0, 0, false};

        
        
        rf.quad_words(0x0);
        rf.pause_time(0x0);
        rf.count_up(false);

        REQUIRE((rf.raw & 0x1ffff) == 0x0);
        
        rf.quad_words(0xff);
        rf.pause_time(0xff);
        rf.count_up(true);

        REQUIRE((rf.raw & 0x1ffff) == 0x1ffff);
        
        rf.quad_words(0xaa);
        rf.pause_time(0xaa);
        rf.count_up(false);

        REQUIRE((rf.raw & 0x1ffff) == 0xaaaa);
        
        rf.quad_words(0x55);
        rf.pause_time(0x55);
        rf.count_up(true);

        REQUIRE((rf.raw & 0x1ffff) == 0x15555);
        
        rf.quad_words(0xef);
        rf.pause_time(0xbe);
        rf.count_up(false);

        REQUIRE((rf.raw & 0x1ffff) == 0xbeef);
    }
}

TEST_CASE("Definition 'TestControlStart'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TestControlStart rf {false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.start());
        
    }

    SECTION("write fields - read raw")
    {
        TestControlStart rf {false};

        
        
        rf.start(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.start(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.start(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.start(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.start(true);

        REQUIRE((rf.raw & 0x1) == true);
    }
}

TEST_CASE("Definition 'TestControlType'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TestControlType rf {TestControlType::Type(0)};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.type() == TestControlType::Type(0x0));
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.type() == TestControlType::Type(0xffff));
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.type() == TestControlType::Type(0xaaaa));
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.type() == TestControlType::Type(0x5555));
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.type() == TestControlType::Type(0xbeef));
        
    }

    SECTION("write fields - read raw")
    {
        TestControlType rf {TestControlType::Type(0)};

        
        
        rf.type(TestControlType::Type(0x0));

        REQUIRE((rf.raw & 0xffff) == 0x0);
        
        rf.type(TestControlType::Type(0xffff));

        REQUIRE((rf.raw & 0xffff) == 0xffff);
        
        rf.type(TestControlType::Type(0xaaaa));

        REQUIRE((rf.raw & 0xffff) == 0xaaaa);
        
        rf.type(TestControlType::Type(0x5555));

        REQUIRE((rf.raw & 0xffff) == 0x5555);
        
        rf.type(TestControlType::Type(0xbeef));

        REQUIRE((rf.raw & 0xffff) == 0xbeef);
    }
}

TEST_CASE("Definition 'TraceBufferSize'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferSize rf {0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.data() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.data() == 0xffffffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.data() == 0xaaaaaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.data() == 0x55555555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.data() == 0xbabebeef);
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferSize rf {0};

        
        
        rf.data(0x0);

        REQUIRE((rf.raw & 0xffffffff) == 0x0);
        
        rf.data(0xffffffff);

        REQUIRE((rf.raw & 0xffffffff) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);

        REQUIRE((rf.raw & 0xffffffff) == 0xaaaaaaaa);
        
        rf.data(0x55555555);

        REQUIRE((rf.raw & 0xffffffff) == 0x55555555);
        
        rf.data(0xbabebeef);

        REQUIRE((rf.raw & 0xffffffff) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'TraceBufferFullThreshold'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferFullThreshold rf {0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.data() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.data() == 0xffffffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.data() == 0xaaaaaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.data() == 0x55555555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.data() == 0xbabebeef);
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferFullThreshold rf {0};

        
        
        rf.data(0x0);

        REQUIRE((rf.raw & 0xffffffff) == 0x0);
        
        rf.data(0xffffffff);

        REQUIRE((rf.raw & 0xffffffff) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);

        REQUIRE((rf.raw & 0xffffffff) == 0xaaaaaaaa);
        
        rf.data(0x55555555);

        REQUIRE((rf.raw & 0xffffffff) == 0x55555555);
        
        rf.data(0xbabebeef);

        REQUIRE((rf.raw & 0xffffffff) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'TraceBufferCounter'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferCounter rf {0, 0, 0, 0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.start_address() == 0x0);
        REQUIRE(rf.size() == 0x0);
        REQUIRE(rf.threshold() == 0x0);
        REQUIRE(rf.wraps() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.start_address() == 0xffff);
        REQUIRE(rf.size() == 0xffff);
        REQUIRE(rf.threshold() == 0xffff);
        REQUIRE(rf.wraps() == 0xffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.start_address() == 0xaaaa);
        REQUIRE(rf.size() == 0xaaaa);
        REQUIRE(rf.threshold() == 0xaaaa);
        REQUIRE(rf.wraps() == 0xaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.start_address() == 0x5555);
        REQUIRE(rf.size() == 0x5555);
        REQUIRE(rf.threshold() == 0x5555);
        REQUIRE(rf.wraps() == 0x5555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.start_address() == 0xbeef);
        REQUIRE(rf.size() == 0xbabe);
        REQUIRE(rf.threshold() == 0xdead);
        REQUIRE(rf.wraps() == 0xcafe);
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferCounter rf {0, 0, 0, 0};

        
        
        rf.start_address(0x0);
        rf.size(0x0);
        rf.threshold(0x0);
        rf.wraps(0x0);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);
        
        rf.start_address(0xffff);
        rf.size(0xffff);
        rf.threshold(0xffff);
        rf.wraps(0xffff);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);
        
        rf.start_address(0xaaaa);
        rf.size(0xaaaa);
        rf.threshold(0xaaaa);
        rf.wraps(0xaaaa);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);
        
        rf.start_address(0x5555);
        rf.size(0x5555);
        rf.threshold(0x5555);
        rf.wraps(0x5555);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);
        
        rf.start_address(0xbeef);
        rf.size(0xbabe);
        rf.threshold(0xdead);
        rf.wraps(0xcafe);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}

TEST_CASE("Definition 'TraceBufferCounterReset'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferCounterReset rf {false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.reset());
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferCounterReset rf {false};

        
        
        rf.reset(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.reset(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.reset(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.reset(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.reset(true);

        REQUIRE((rf.raw & 0x1) == true);
    }
}

TEST_CASE("Definition 'TraceBufferFreeSpace'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferFreeSpace rf {0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.data() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.data() == 0xffffffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.data() == 0xaaaaaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.data() == 0x55555555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.data() == 0xbabebeef);
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferFreeSpace rf {0};

        
        
        rf.data(0x0);

        REQUIRE((rf.raw & 0xffffffff) == 0x0);
        
        rf.data(0xffffffff);

        REQUIRE((rf.raw & 0xffffffff) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);

        REQUIRE((rf.raw & 0xffffffff) == 0xaaaaaaaa);
        
        rf.data(0x55555555);

        REQUIRE((rf.raw & 0xffffffff) == 0x55555555);
        
        rf.data(0xbabebeef);

        REQUIRE((rf.raw & 0xffffffff) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'TraceBufferInit'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceBufferInit rf {false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.start());
        
    }

    SECTION("write fields - read raw")
    {
        TraceBufferInit rf {false};

        
        
        rf.start(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.start(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.start(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.start(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.start(true);

        REQUIRE((rf.raw & 0x1) == true);
    }
}

TEST_CASE("Definition 'HicannBufferSize'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferSize rf {0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.data() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.data() == 0xffffffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.data() == 0xaaaaaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.data() == 0x55555555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.data() == 0xbabebeef);
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferSize rf {0};

        
        
        rf.data(0x0);

        REQUIRE((rf.raw & 0xffffffff) == 0x0);
        
        rf.data(0xffffffff);

        REQUIRE((rf.raw & 0xffffffff) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);

        REQUIRE((rf.raw & 0xffffffff) == 0xaaaaaaaa);
        
        rf.data(0x55555555);

        REQUIRE((rf.raw & 0xffffffff) == 0x55555555);
        
        rf.data(0xbabebeef);

        REQUIRE((rf.raw & 0xffffffff) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'HicannBufferFullThreshold'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferFullThreshold rf {0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.data() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.data() == 0xffffffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.data() == 0xaaaaaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.data() == 0x55555555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.data() == 0xbabebeef);
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferFullThreshold rf {0};

        
        
        rf.data(0x0);

        REQUIRE((rf.raw & 0xffffffff) == 0x0);
        
        rf.data(0xffffffff);

        REQUIRE((rf.raw & 0xffffffff) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);

        REQUIRE((rf.raw & 0xffffffff) == 0xaaaaaaaa);
        
        rf.data(0x55555555);

        REQUIRE((rf.raw & 0xffffffff) == 0x55555555);
        
        rf.data(0xbabebeef);

        REQUIRE((rf.raw & 0xffffffff) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'HicannBufferCounter'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferCounter rf {0, 0, 0, 0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.start_address() == 0x0);
        REQUIRE(rf.size() == 0x0);
        REQUIRE(rf.threshold() == 0x0);
        REQUIRE(rf.wraps() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.start_address() == 0xffff);
        REQUIRE(rf.size() == 0xffff);
        REQUIRE(rf.threshold() == 0xffff);
        REQUIRE(rf.wraps() == 0xffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.start_address() == 0xaaaa);
        REQUIRE(rf.size() == 0xaaaa);
        REQUIRE(rf.threshold() == 0xaaaa);
        REQUIRE(rf.wraps() == 0xaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.start_address() == 0x5555);
        REQUIRE(rf.size() == 0x5555);
        REQUIRE(rf.threshold() == 0x5555);
        REQUIRE(rf.wraps() == 0x5555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.start_address() == 0xbeef);
        REQUIRE(rf.size() == 0xbabe);
        REQUIRE(rf.threshold() == 0xdead);
        REQUIRE(rf.wraps() == 0xcafe);
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferCounter rf {0, 0, 0, 0};

        
        
        rf.start_address(0x0);
        rf.size(0x0);
        rf.threshold(0x0);
        rf.wraps(0x0);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);
        
        rf.start_address(0xffff);
        rf.size(0xffff);
        rf.threshold(0xffff);
        rf.wraps(0xffff);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);
        
        rf.start_address(0xaaaa);
        rf.size(0xaaaa);
        rf.threshold(0xaaaa);
        rf.wraps(0xaaaa);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);
        
        rf.start_address(0x5555);
        rf.size(0x5555);
        rf.threshold(0x5555);
        rf.wraps(0x5555);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);
        
        rf.start_address(0xbeef);
        rf.size(0xbabe);
        rf.threshold(0xdead);
        rf.wraps(0xcafe);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}

TEST_CASE("Definition 'HicannBufferCounterReset'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferCounterReset rf {false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.reset());
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferCounterReset rf {false};

        
        
        rf.reset(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.reset(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.reset(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.reset(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.reset(true);

        REQUIRE((rf.raw & 0x1) == true);
    }
}

TEST_CASE("Definition 'HicannBufferFreeSpace'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferFreeSpace rf {0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.data() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.data() == 0xffffffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.data() == 0xaaaaaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.data() == 0x55555555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.data() == 0xbabebeef);
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferFreeSpace rf {0};

        
        
        rf.data(0x0);

        REQUIRE((rf.raw & 0xffffffff) == 0x0);
        
        rf.data(0xffffffff);

        REQUIRE((rf.raw & 0xffffffff) == 0xffffffff);
        
        rf.data(0xaaaaaaaa);

        REQUIRE((rf.raw & 0xffffffff) == 0xaaaaaaaa);
        
        rf.data(0x55555555);

        REQUIRE((rf.raw & 0xffffffff) == 0x55555555);
        
        rf.data(0xbabebeef);

        REQUIRE((rf.raw & 0xffffffff) == 0xbabebeef);
    }
}

TEST_CASE("Definition 'HicannBufferInit'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannBufferInit rf {false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.start());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.start());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.start());
        
    }

    SECTION("write fields - read raw")
    {
        HicannBufferInit rf {false};

        
        
        rf.start(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.start(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.start(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.start(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.start(true);

        REQUIRE((rf.raw & 0x1) == true);
    }
}

TEST_CASE("Definition 'CounterReset'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        CounterReset rf {false};

        
        rf.raw = 0x0;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(!rf.reset());
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.reset());
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.reset());
        
    }

    SECTION("write fields - read raw")
    {
        CounterReset rf {false};

        
        
        rf.reset(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.reset(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.reset(false);

        REQUIRE((rf.raw & 0x1) == false);
        
        rf.reset(true);

        REQUIRE((rf.raw & 0x1) == true);
        
        rf.reset(true);

        REQUIRE((rf.raw & 0x1) == true);
    }
}

TEST_CASE("Definition 'HostEndpoint'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HostEndpoint rf {0, 0, 0, 0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.node_id() == 0x0);
        REQUIRE(rf.protection_domain() == 0x0);
        REQUIRE(rf.vpid() == 0x0);
        REQUIRE(rf.mode() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.node_id() == 0xffff);
        REQUIRE(rf.protection_domain() == 0xffff);
        REQUIRE(rf.vpid() == 0x3ff);
        REQUIRE(rf.mode() == 0x3f);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.node_id() == 0xaaaa);
        REQUIRE(rf.protection_domain() == 0xaaaa);
        REQUIRE(rf.vpid() == 0x2aa);
        REQUIRE(rf.mode() == 0x2a);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.node_id() == 0x5555);
        REQUIRE(rf.protection_domain() == 0x5555);
        REQUIRE(rf.vpid() == 0x155);
        REQUIRE(rf.mode() == 0x15);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.node_id() == 0xbeef);
        REQUIRE(rf.protection_domain() == 0xbabe);
        REQUIRE(rf.vpid() == 0x2ad);
        REQUIRE(rf.mode() == 0x37);
        
    }

    SECTION("write fields - read raw")
    {
        HostEndpoint rf {0, 0, 0, 0};

        
        
        rf.node_id(0x0);
        rf.protection_domain(0x0);
        rf.vpid(0x0);
        rf.mode(0x0);

        REQUIRE((rf.raw & 0xffffffffffff) == 0x0);
        
        rf.node_id(0xffff);
        rf.protection_domain(0xffff);
        rf.vpid(0x3ff);
        rf.mode(0x3f);

        REQUIRE((rf.raw & 0xffffffffffff) == 0xffffffffffff);
        
        rf.node_id(0xaaaa);
        rf.protection_domain(0xaaaa);
        rf.vpid(0x2aa);
        rf.mode(0x2a);

        REQUIRE((rf.raw & 0xffffffffffff) == 0xaaaaaaaaaaaa);
        
        rf.node_id(0x5555);
        rf.protection_domain(0x5555);
        rf.vpid(0x155);
        rf.mode(0x15);

        REQUIRE((rf.raw & 0xffffffffffff) == 0x555555555555);
        
        rf.node_id(0xbeef);
        rf.protection_domain(0xbabe);
        rf.vpid(0x2ad);
        rf.mode(0x37);

        REQUIRE((rf.raw & 0xffffffffffff) == 0xdeadbabebeef);
    }
}

TEST_CASE("Definition 'TraceNotificationBehaviour'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceNotificationBehaviour rf {0, 0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.timeout() == 0x0);
        REQUIRE(rf.frequency() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.timeout() == 0xffffffff);
        REQUIRE(rf.frequency() == 0xffffffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.timeout() == 0xaaaaaaaa);
        REQUIRE(rf.frequency() == 0xaaaaaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.timeout() == 0x55555555);
        REQUIRE(rf.frequency() == 0x55555555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.timeout() == 0xbabebeef);
        REQUIRE(rf.frequency() == 0xcafedead);
        
    }

    SECTION("write fields - read raw")
    {
        TraceNotificationBehaviour rf {0, 0};

        
        
        rf.timeout(0x0);
        rf.frequency(0x0);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);
        
        rf.timeout(0xffffffff);
        rf.frequency(0xffffffff);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);
        
        rf.timeout(0xaaaaaaaa);
        rf.frequency(0xaaaaaaaa);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);
        
        rf.timeout(0x55555555);
        rf.frequency(0x55555555);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);
        
        rf.timeout(0xbabebeef);
        rf.frequency(0xcafedead);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}

TEST_CASE("Definition 'HicannNotificationBehaviour'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannNotificationBehaviour rf {0, 0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.timeout() == 0x0);
        REQUIRE(rf.frequency() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.timeout() == 0xffffffff);
        REQUIRE(rf.frequency() == 0xffffffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.timeout() == 0xaaaaaaaa);
        REQUIRE(rf.frequency() == 0xaaaaaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.timeout() == 0x55555555);
        REQUIRE(rf.frequency() == 0x55555555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.timeout() == 0xbabebeef);
        REQUIRE(rf.frequency() == 0xcafedead);
        
    }

    SECTION("write fields - read raw")
    {
        HicannNotificationBehaviour rf {0, 0};

        
        
        rf.timeout(0x0);
        rf.frequency(0x0);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);
        
        rf.timeout(0xffffffff);
        rf.frequency(0xffffffff);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);
        
        rf.timeout(0xaaaaaaaa);
        rf.frequency(0xaaaaaaaa);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);
        
        rf.timeout(0x55555555);
        rf.frequency(0x55555555);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);
        
        rf.timeout(0xbabebeef);
        rf.frequency(0xcafedead);

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}

TEST_CASE("Definition 'Info'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        Info rf {0, 0};

        
        rf.raw = 0x0;

        
        REQUIRE(rf.guid() == 0x0);
        REQUIRE(rf.node_id() == 0x0);
        
        rf.raw = 0xffffffffffffffff;

        
        REQUIRE(rf.guid() == 0xffffff);
        REQUIRE(rf.node_id() == 0xffff);
        
        rf.raw = 0xaaaaaaaaaaaaaaaa;

        
        REQUIRE(rf.guid() == 0xaaaaaa);
        REQUIRE(rf.node_id() == 0xaaaa);
        
        rf.raw = 0x5555555555555555;

        
        REQUIRE(rf.guid() == 0x555555);
        REQUIRE(rf.node_id() == 0x5555);
        
        rf.raw = 0xcafedeadbabebeef;

        
        REQUIRE(rf.guid() == 0xbebeef);
        REQUIRE(rf.node_id() == 0xadba);
        
    }

    SECTION("write fields - read raw")
    {
        Info rf {0, 0};

        
        
        rf.guid(0x0);
        rf.node_id(0x0);

        REQUIRE((rf.raw & 0xffffffffff) == 0x0);
        
        rf.guid(0xffffff);
        rf.node_id(0xffff);

        REQUIRE((rf.raw & 0xffffffffff) == 0xffffffffff);
        
        rf.guid(0xaaaaaa);
        rf.node_id(0xaaaa);

        REQUIRE((rf.raw & 0xffffffffff) == 0xaaaaaaaaaa);
        
        rf.guid(0x555555);
        rf.node_id(0x5555);

        REQUIRE((rf.raw & 0xffffffffff) == 0x5555555555);
        
        rf.guid(0xbebeef);
        rf.node_id(0xadba);

        REQUIRE((rf.raw & 0xffffffffff) == 0xadbabebeef);
    }
}
