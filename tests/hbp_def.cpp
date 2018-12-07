/**
 * This is a generated file - do not change it
 * 07.12.2018 20:20:17.037022 
 */

#include <catch.hpp>
#include <extoll/hbp_def.h>


using namespace extoll::library::rf;

TEST_CASE("Generated definition 'Reset'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        Reset rf;

        rf.raw = 0x0;

        CHECK(rf.core == 0x0);
        CHECK(rf.hicann == 0x0);
        CHECK(rf.arq == 0x0);
        CHECK(rf.pulse_mem == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.core == 0x1);
        CHECK(rf.hicann == 0x1);
        CHECK(rf.arq == 0x1);
        CHECK(rf.pulse_mem == 0x1);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.core == 0x0);
        CHECK(rf.hicann == 0x1);
        CHECK(rf.arq == 0x0);
        CHECK(rf.pulse_mem == 0x1);

        rf.raw = 0x5555555555555555;

        CHECK(rf.core == 0x1);
        CHECK(rf.hicann == 0x0);
        CHECK(rf.arq == 0x1);
        CHECK(rf.pulse_mem == 0x0);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.core == 0x1);
        CHECK(rf.hicann == 0x1);
        CHECK(rf.arq == 0x1);
        CHECK(rf.pulse_mem == 0x1);
    }

    SECTION("write fields - read raw")
    {
        Reset rf;

        rf.core = 0x0;
        rf.hicann = 0x0;
        rf.arq = 0x0;
        rf.pulse_mem = 0x0;

        REQUIRE((rf.raw & 0xf) == 0x0);

        rf.core = 0x1;
        rf.hicann = 0x1;
        rf.arq = 0x1;
        rf.pulse_mem = 0x1;

        REQUIRE((rf.raw & 0xf) == 0xf);

        rf.core = 0x0;
        rf.hicann = 0x1;
        rf.arq = 0x0;
        rf.pulse_mem = 0x1;

        REQUIRE((rf.raw & 0xf) == 0xa);

        rf.core = 0x1;
        rf.hicann = 0x0;
        rf.arq = 0x1;
        rf.pulse_mem = 0x0;

        REQUIRE((rf.raw & 0xf) == 0x5);

        rf.core = 0x1;
        rf.hicann = 0x1;
        rf.arq = 0x1;
        rf.pulse_mem = 0x1;

        REQUIRE((rf.raw & 0xf) == 0xf);
    }
}
TEST_CASE("Generated definition 'JtagCmd'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        JtagCmd rf;

        rf.raw = 0x0;

        CHECK(rf.type == 0x0);
        CHECK(rf.length == 0x0);
        CHECK(rf.pause == 0x0);
        CHECK(rf.execute == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.type == 0x7);
        CHECK(rf.length == 0x3ff);
        CHECK(rf.pause == 0x1);
        CHECK(rf.execute == 0x1);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.type == 0x2);
        CHECK(rf.length == 0x155);
        CHECK(rf.pause == 0x1);
        CHECK(rf.execute == 0x0);

        rf.raw = 0x5555555555555555;

        CHECK(rf.type == 0x5);
        CHECK(rf.length == 0x2aa);
        CHECK(rf.pause == 0x0);
        CHECK(rf.execute == 0x1);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.type == 0x7);
        CHECK(rf.length == 0x3dd);
        CHECK(rf.pause == 0x1);
        CHECK(rf.execute == 0x0);
    }

    SECTION("write fields - read raw")
    {
        JtagCmd rf;

        rf.type = 0x0;
        rf.length = 0x0;
        rf.pause = 0x0;
        rf.execute = 0x0;

        REQUIRE((rf.raw & 0x7fff) == 0x0);

        rf.type = 0x7;
        rf.length = 0x3ff;
        rf.pause = 0x1;
        rf.execute = 0x1;

        REQUIRE((rf.raw & 0x7fff) == 0x7fff);

        rf.type = 0x2;
        rf.length = 0x155;
        rf.pause = 0x1;
        rf.execute = 0x0;

        REQUIRE((rf.raw & 0x7fff) == 0x2aaa);

        rf.type = 0x5;
        rf.length = 0x2aa;
        rf.pause = 0x0;
        rf.execute = 0x1;

        REQUIRE((rf.raw & 0x7fff) == 0x5555);

        rf.type = 0x7;
        rf.length = 0x3dd;
        rf.pause = 0x1;
        rf.execute = 0x0;

        REQUIRE((rf.raw & 0x7fff) == 0x3eef);
    }
}
TEST_CASE("Generated definition 'JtagStatus'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        JtagStatus rf;

        rf.raw = 0x0;

        CHECK(rf.clock_enabled == 0x0);
        CHECK(rf.paused == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.clock_enabled == 0x1);
        CHECK(rf.paused == 0x1);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.clock_enabled == 0x0);
        CHECK(rf.paused == 0x1);

        rf.raw = 0x5555555555555555;

        CHECK(rf.clock_enabled == 0x1);
        CHECK(rf.paused == 0x0);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.clock_enabled == 0x1);
        CHECK(rf.paused == 0x1);
    }

    SECTION("write fields - read raw")
    {
        JtagStatus rf;

        rf.clock_enabled = 0x0;
        rf.paused = 0x0;

        REQUIRE((rf.raw & 0x3) == 0x0);

        rf.clock_enabled = 0x1;
        rf.paused = 0x1;

        REQUIRE((rf.raw & 0x3) == 0x3);

        rf.clock_enabled = 0x0;
        rf.paused = 0x1;

        REQUIRE((rf.raw & 0x3) == 0x2);

        rf.clock_enabled = 0x1;
        rf.paused = 0x0;

        REQUIRE((rf.raw & 0x3) == 0x1);

        rf.clock_enabled = 0x1;
        rf.paused = 0x1;

        REQUIRE((rf.raw & 0x3) == 0x3);
    }
}
TEST_CASE("Generated definition 'JtagSend'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        JtagSend rf;

        rf.raw = 0x0;

        CHECK(rf.data == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.data == 0xffffffffffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.data == 0xaaaaaaaaaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.data == 0x5555555555555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.data == 0xcafedeadbabebeef);
    }

    SECTION("write fields - read raw")
    {
        JtagSend rf;

        rf.data = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.data = 0xffffffffffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.data = 0xaaaaaaaaaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.data = 0x5555555555555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.data = 0xcafedeadbabebeef;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'JtagReceive'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        JtagReceive rf;

        rf.raw = 0x0;

        CHECK(rf.data == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.data == 0xffffffffffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.data == 0xaaaaaaaaaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.data == 0x5555555555555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.data == 0xcafedeadbabebeef);
    }

    SECTION("write fields - read raw")
    {
        JtagReceive rf;

        rf.data = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.data = 0xffffffffffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.data = 0xaaaaaaaaaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.data = 0x5555555555555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.data = 0xcafedeadbabebeef;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'HicannIfState'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfState rf;

        rf.raw = 0x0;

        CHECK(rf.channel_status == 0x0);
        CHECK(rf.crc_count == 0x0);
        CHECK(rf.systime == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.channel_status == 0xff);
        CHECK(rf.crc_count == 0xff);
        CHECK(rf.systime == 0x3fff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.channel_status == 0xaa);
        CHECK(rf.crc_count == 0xaa);
        CHECK(rf.systime == 0x2aaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.channel_status == 0x55);
        CHECK(rf.crc_count == 0x55);
        CHECK(rf.systime == 0x1555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.channel_status == 0xef);
        CHECK(rf.crc_count == 0xbe);
        CHECK(rf.systime == 0x3abe);
    }

    SECTION("write fields - read raw")
    {
        HicannIfState rf;

        rf.channel_status = 0x0;
        rf.crc_count = 0x0;
        rf.systime = 0x0;

        REQUIRE((rf.raw & 0x3fffffff) == 0x0);

        rf.channel_status = 0xff;
        rf.crc_count = 0xff;
        rf.systime = 0x3fff;

        REQUIRE((rf.raw & 0x3fffffff) == 0x3fffffff);

        rf.channel_status = 0xaa;
        rf.crc_count = 0xaa;
        rf.systime = 0x2aaa;

        REQUIRE((rf.raw & 0x3fffffff) == 0x2aaaaaaa);

        rf.channel_status = 0x55;
        rf.crc_count = 0x55;
        rf.systime = 0x1555;

        REQUIRE((rf.raw & 0x3fffffff) == 0x15555555);

        rf.channel_status = 0xef;
        rf.crc_count = 0xbe;
        rf.systime = 0x3abe;

        REQUIRE((rf.raw & 0x3fffffff) == 0x3abebeef);
    }
}
TEST_CASE("Generated definition 'HicannIfRxConfig'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfRxConfig rf;

        rf.raw = 0x0;

        CHECK(rf.data == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.data == 0xffffffffffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.data == 0xaaaaaaaaaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.data == 0x5555555555555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.data == 0xcafedeadbabebeef);
    }

    SECTION("write fields - read raw")
    {
        HicannIfRxConfig rf;

        rf.data = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.data = 0xffffffffffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.data = 0xaaaaaaaaaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.data = 0x5555555555555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.data = 0xcafedeadbabebeef;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'HicannIfRxPulse'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfRxPulse rf;

        rf.raw = 0x0;

        CHECK(rf.data == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.data == 0xffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.data == 0xaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.data == 0x555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.data == 0xbebeef);
    }

    SECTION("write fields - read raw")
    {
        HicannIfRxPulse rf;

        rf.data = 0x0;

        REQUIRE((rf.raw & 0xffffff) == 0x0);

        rf.data = 0xffffff;

        REQUIRE((rf.raw & 0xffffff) == 0xffffff);

        rf.data = 0xaaaaaa;

        REQUIRE((rf.raw & 0xffffff) == 0xaaaaaa);

        rf.data = 0x555555;

        REQUIRE((rf.raw & 0xffffff) == 0x555555);

        rf.data = 0xbebeef;

        REQUIRE((rf.raw & 0xffffff) == 0xbebeef);
    }
}
TEST_CASE("Generated definition 'HicannIfConfig'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfConfig rf;

        rf.raw = 0x0;

        CHECK(rf.start_link == 0x0);
        CHECK(rf.loopback_enable == 0x0);
        CHECK(rf.auto_init == 0x0);
        CHECK(rf.init_master == 0x0);
        CHECK(rf.use_timestamp == 0x0);
        CHECK(rf.auto_limit == 0x0);
        CHECK(rf.pulse_protocol == 0x0);
        CHECK(rf.config_protocol == 0x0);
        CHECK(rf.heap_mode == 0x0);
        CHECK(rf.limit == 0x0);
        CHECK(rf.dc_coding == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.start_link == 0x1);
        CHECK(rf.loopback_enable == 0x1);
        CHECK(rf.auto_init == 0x1);
        CHECK(rf.init_master == 0x1);
        CHECK(rf.use_timestamp == 0x1);
        CHECK(rf.auto_limit == 0x1);
        CHECK(rf.pulse_protocol == 0x1);
        CHECK(rf.config_protocol == 0x1);
        CHECK(rf.heap_mode == 0xff);
        CHECK(rf.limit == 0x7ff);
        CHECK(rf.dc_coding == 0x1);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.start_link == 0x0);
        CHECK(rf.loopback_enable == 0x1);
        CHECK(rf.auto_init == 0x0);
        CHECK(rf.init_master == 0x1);
        CHECK(rf.use_timestamp == 0x0);
        CHECK(rf.auto_limit == 0x1);
        CHECK(rf.pulse_protocol == 0x0);
        CHECK(rf.config_protocol == 0x1);
        CHECK(rf.heap_mode == 0xaa);
        CHECK(rf.limit == 0x2aa);
        CHECK(rf.dc_coding == 0x1);

        rf.raw = 0x5555555555555555;

        CHECK(rf.start_link == 0x1);
        CHECK(rf.loopback_enable == 0x0);
        CHECK(rf.auto_init == 0x1);
        CHECK(rf.init_master == 0x0);
        CHECK(rf.use_timestamp == 0x1);
        CHECK(rf.auto_limit == 0x0);
        CHECK(rf.pulse_protocol == 0x1);
        CHECK(rf.config_protocol == 0x0);
        CHECK(rf.heap_mode == 0x55);
        CHECK(rf.limit == 0x555);
        CHECK(rf.dc_coding == 0x0);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.start_link == 0x1);
        CHECK(rf.loopback_enable == 0x1);
        CHECK(rf.auto_init == 0x1);
        CHECK(rf.init_master == 0x1);
        CHECK(rf.use_timestamp == 0x0);
        CHECK(rf.auto_limit == 0x1);
        CHECK(rf.pulse_protocol == 0x1);
        CHECK(rf.config_protocol == 0x1);
        CHECK(rf.heap_mode == 0xbe);
        CHECK(rf.limit == 0x2be);
        CHECK(rf.dc_coding == 0x1);
    }

    SECTION("write fields - read raw")
    {
        HicannIfConfig rf;

        rf.start_link = 0x0;
        rf.loopback_enable = 0x0;
        rf.auto_init = 0x0;
        rf.init_master = 0x0;
        rf.use_timestamp = 0x0;
        rf.auto_limit = 0x0;
        rf.pulse_protocol = 0x0;
        rf.config_protocol = 0x0;
        rf.heap_mode = 0x0;
        rf.limit = 0x0;
        rf.dc_coding = 0x0;

        REQUIRE((rf.raw & 0xfffffff) == 0x0);

        rf.start_link = 0x1;
        rf.loopback_enable = 0x1;
        rf.auto_init = 0x1;
        rf.init_master = 0x1;
        rf.use_timestamp = 0x1;
        rf.auto_limit = 0x1;
        rf.pulse_protocol = 0x1;
        rf.config_protocol = 0x1;
        rf.heap_mode = 0xff;
        rf.limit = 0x7ff;
        rf.dc_coding = 0x1;

        REQUIRE((rf.raw & 0xfffffff) == 0xfffffff);

        rf.start_link = 0x0;
        rf.loopback_enable = 0x1;
        rf.auto_init = 0x0;
        rf.init_master = 0x1;
        rf.use_timestamp = 0x0;
        rf.auto_limit = 0x1;
        rf.pulse_protocol = 0x0;
        rf.config_protocol = 0x1;
        rf.heap_mode = 0xaa;
        rf.limit = 0x2aa;
        rf.dc_coding = 0x1;

        REQUIRE((rf.raw & 0xfffffff) == 0xaaaaaaa);

        rf.start_link = 0x1;
        rf.loopback_enable = 0x0;
        rf.auto_init = 0x1;
        rf.init_master = 0x0;
        rf.use_timestamp = 0x1;
        rf.auto_limit = 0x0;
        rf.pulse_protocol = 0x1;
        rf.config_protocol = 0x0;
        rf.heap_mode = 0x55;
        rf.limit = 0x555;
        rf.dc_coding = 0x0;

        REQUIRE((rf.raw & 0xfffffff) == 0x5555555);

        rf.start_link = 0x1;
        rf.loopback_enable = 0x1;
        rf.auto_init = 0x1;
        rf.init_master = 0x1;
        rf.use_timestamp = 0x0;
        rf.auto_limit = 0x1;
        rf.pulse_protocol = 0x1;
        rf.config_protocol = 0x1;
        rf.heap_mode = 0xbe;
        rf.limit = 0x2be;
        rf.dc_coding = 0x1;

        REQUIRE((rf.raw & 0xfffffff) == 0xabebeef);
    }
}
TEST_CASE("Generated definition 'HicannIfControls'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfControls rf;

        rf.raw = 0x0;

        CHECK(rf.tx_hicann_pulse_enable == 0x0);
        CHECK(rf.tx_hicann_config_enable == 0x0);
        CHECK(rf.routing_data_enable == 0x0);
        CHECK(rf.channel_reset == 0x0);
        CHECK(rf.crc_count_reset == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.tx_hicann_pulse_enable == 0x1);
        CHECK(rf.tx_hicann_config_enable == 0x1);
        CHECK(rf.routing_data_enable == 0x1);
        CHECK(rf.channel_reset == 0x1);
        CHECK(rf.crc_count_reset == 0x1);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.tx_hicann_pulse_enable == 0x0);
        CHECK(rf.tx_hicann_config_enable == 0x1);
        CHECK(rf.routing_data_enable == 0x0);
        CHECK(rf.channel_reset == 0x1);
        CHECK(rf.crc_count_reset == 0x0);

        rf.raw = 0x5555555555555555;

        CHECK(rf.tx_hicann_pulse_enable == 0x1);
        CHECK(rf.tx_hicann_config_enable == 0x0);
        CHECK(rf.routing_data_enable == 0x1);
        CHECK(rf.channel_reset == 0x0);
        CHECK(rf.crc_count_reset == 0x1);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.tx_hicann_pulse_enable == 0x1);
        CHECK(rf.tx_hicann_config_enable == 0x1);
        CHECK(rf.routing_data_enable == 0x1);
        CHECK(rf.channel_reset == 0x1);
        CHECK(rf.crc_count_reset == 0x0);
    }

    SECTION("write fields - read raw")
    {
        HicannIfControls rf;

        rf.tx_hicann_pulse_enable = 0x0;
        rf.tx_hicann_config_enable = 0x0;
        rf.routing_data_enable = 0x0;
        rf.channel_reset = 0x0;
        rf.crc_count_reset = 0x0;

        REQUIRE((rf.raw & 0x1f) == 0x0);

        rf.tx_hicann_pulse_enable = 0x1;
        rf.tx_hicann_config_enable = 0x1;
        rf.routing_data_enable = 0x1;
        rf.channel_reset = 0x1;
        rf.crc_count_reset = 0x1;

        REQUIRE((rf.raw & 0x1f) == 0x1f);

        rf.tx_hicann_pulse_enable = 0x0;
        rf.tx_hicann_config_enable = 0x1;
        rf.routing_data_enable = 0x0;
        rf.channel_reset = 0x1;
        rf.crc_count_reset = 0x0;

        REQUIRE((rf.raw & 0x1f) == 0xa);

        rf.tx_hicann_pulse_enable = 0x1;
        rf.tx_hicann_config_enable = 0x0;
        rf.routing_data_enable = 0x1;
        rf.channel_reset = 0x0;
        rf.crc_count_reset = 0x1;

        REQUIRE((rf.raw & 0x1f) == 0x15);

        rf.tx_hicann_pulse_enable = 0x1;
        rf.tx_hicann_config_enable = 0x1;
        rf.routing_data_enable = 0x1;
        rf.channel_reset = 0x1;
        rf.crc_count_reset = 0x0;

        REQUIRE((rf.raw & 0x1f) == 0xf);
    }
}
TEST_CASE("Generated definition 'HicannIfTxData'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannIfTxData rf;

        rf.raw = 0x0;

        CHECK(rf.data == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.data == 0xffffffffffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.data == 0xaaaaaaaaaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.data == 0x5555555555555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.data == 0xcafedeadbabebeef);
    }

    SECTION("write fields - read raw")
    {
        HicannIfTxData rf;

        rf.data = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.data = 0xffffffffffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.data = 0xaaaaaaaaaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.data = 0x5555555555555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.data = 0xcafedeadbabebeef;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'HicannPacketGen'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannPacketGen rf;

        rf.raw = 0x0;

        CHECK(rf.count == 0x0);
        CHECK(rf.error == 0x0);
        CHECK(rf.enable == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.count == 0x1ffffff);
        CHECK(rf.error == 0x1);
        CHECK(rf.enable == 0x1);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.count == 0xaaaaaa);
        CHECK(rf.error == 0x1);
        CHECK(rf.enable == 0x0);

        rf.raw = 0x5555555555555555;

        CHECK(rf.count == 0x1555555);
        CHECK(rf.error == 0x0);
        CHECK(rf.enable == 0x1);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.count == 0xbebeef);
        CHECK(rf.error == 0x1);
        CHECK(rf.enable == 0x0);
    }

    SECTION("write fields - read raw")
    {
        HicannPacketGen rf;

        rf.count = 0x0;
        rf.error = 0x0;
        rf.enable = 0x0;

        REQUIRE((rf.raw & 0x7ffffff) == 0x0);

        rf.count = 0x1ffffff;
        rf.error = 0x1;
        rf.enable = 0x1;

        REQUIRE((rf.raw & 0x7ffffff) == 0x7ffffff);

        rf.count = 0xaaaaaa;
        rf.error = 0x1;
        rf.enable = 0x0;

        REQUIRE((rf.raw & 0x7ffffff) == 0x2aaaaaa);

        rf.count = 0x1555555;
        rf.error = 0x0;
        rf.enable = 0x1;

        REQUIRE((rf.raw & 0x7ffffff) == 0x5555555);

        rf.count = 0xbebeef;
        rf.error = 0x1;
        rf.enable = 0x0;

        REQUIRE((rf.raw & 0x7ffffff) == 0x2bebeef);
    }
}
TEST_CASE("Generated definition 'HicannChannel'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannChannel rf;

        rf.raw = 0x0;

        CHECK(rf.number == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.number == 0x7);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.number == 0x2);

        rf.raw = 0x5555555555555555;

        CHECK(rf.number == 0x5);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.number == 0x7);
    }

    SECTION("write fields - read raw")
    {
        HicannChannel rf;

        rf.number = 0x0;

        REQUIRE((rf.raw & 0x7) == 0x0);

        rf.number = 0x7;

        REQUIRE((rf.raw & 0x7) == 0x7);

        rf.number = 0x2;

        REQUIRE((rf.raw & 0x7) == 0x2);

        rf.number = 0x5;

        REQUIRE((rf.raw & 0x7) == 0x5);

        rf.number = 0x7;

        REQUIRE((rf.raw & 0x7) == 0x7);
    }
}
TEST_CASE("Generated definition 'ArqTimings'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        ArqTimings rf;

        rf.raw = 0x0;

        CHECK(rf.master_timeout == 0x0);
        CHECK(rf.target_timeout == 0x0);
        CHECK(rf.arbiter_delay == 0x0);
        CHECK(rf.bit == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.master_timeout == 0x3ff);
        CHECK(rf.target_timeout == 0x3ff);
        CHECK(rf.arbiter_delay == 0x1f);
        CHECK(rf.bit == 0x1);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.master_timeout == 0x2aa);
        CHECK(rf.target_timeout == 0x2aa);
        CHECK(rf.arbiter_delay == 0xa);
        CHECK(rf.bit == 0x1);

        rf.raw = 0x5555555555555555;

        CHECK(rf.master_timeout == 0x155);
        CHECK(rf.target_timeout == 0x155);
        CHECK(rf.arbiter_delay == 0x15);
        CHECK(rf.bit == 0x0);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.master_timeout == 0x2ef);
        CHECK(rf.target_timeout == 0x3af);
        CHECK(rf.arbiter_delay == 0xb);
        CHECK(rf.bit == 0x1);
    }

    SECTION("write fields - read raw")
    {
        ArqTimings rf;

        rf.master_timeout = 0x0;
        rf.target_timeout = 0x0;
        rf.arbiter_delay = 0x0;
        rf.bit = 0x0;

        REQUIRE((rf.raw & 0x3ffffff) == 0x0);

        rf.master_timeout = 0x3ff;
        rf.target_timeout = 0x3ff;
        rf.arbiter_delay = 0x1f;
        rf.bit = 0x1;

        REQUIRE((rf.raw & 0x3ffffff) == 0x3ffffff);

        rf.master_timeout = 0x2aa;
        rf.target_timeout = 0x2aa;
        rf.arbiter_delay = 0xa;
        rf.bit = 0x1;

        REQUIRE((rf.raw & 0x3ffffff) == 0x2aaaaaa);

        rf.master_timeout = 0x155;
        rf.target_timeout = 0x155;
        rf.arbiter_delay = 0x15;
        rf.bit = 0x0;

        REQUIRE((rf.raw & 0x3ffffff) == 0x1555555);

        rf.master_timeout = 0x2ef;
        rf.target_timeout = 0x3af;
        rf.arbiter_delay = 0xb;
        rf.bit = 0x1;

        REQUIRE((rf.raw & 0x3ffffff) == 0x2bebeef);
    }
}
TEST_CASE("Generated definition 'HostEndpoint'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HostEndpoint rf;

        rf.raw = 0x0;

        CHECK(rf.node_id == 0x0);
        CHECK(rf.protection_domain == 0x0);
        CHECK(rf.vpid == 0x0);
        CHECK(rf.mode == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.node_id == 0xffff);
        CHECK(rf.protection_domain == 0xffff);
        CHECK(rf.vpid == 0x3ff);
        CHECK(rf.mode == 0x3f);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.node_id == 0xaaaa);
        CHECK(rf.protection_domain == 0xaaaa);
        CHECK(rf.vpid == 0x2aa);
        CHECK(rf.mode == 0x2a);

        rf.raw = 0x5555555555555555;

        CHECK(rf.node_id == 0x5555);
        CHECK(rf.protection_domain == 0x5555);
        CHECK(rf.vpid == 0x155);
        CHECK(rf.mode == 0x15);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.node_id == 0xbeef);
        CHECK(rf.protection_domain == 0xbabe);
        CHECK(rf.vpid == 0x2ad);
        CHECK(rf.mode == 0x37);
    }

    SECTION("write fields - read raw")
    {
        HostEndpoint rf;

        rf.node_id = 0x0;
        rf.protection_domain = 0x0;
        rf.vpid = 0x0;
        rf.mode = 0x0;

        REQUIRE((rf.raw & 0xffffffffffff) == 0x0);

        rf.node_id = 0xffff;
        rf.protection_domain = 0xffff;
        rf.vpid = 0x3ff;
        rf.mode = 0x3f;

        REQUIRE((rf.raw & 0xffffffffffff) == 0xffffffffffff);

        rf.node_id = 0xaaaa;
        rf.protection_domain = 0xaaaa;
        rf.vpid = 0x2aa;
        rf.mode = 0x2a;

        REQUIRE((rf.raw & 0xffffffffffff) == 0xaaaaaaaaaaaa);

        rf.node_id = 0x5555;
        rf.protection_domain = 0x5555;
        rf.vpid = 0x155;
        rf.mode = 0x15;

        REQUIRE((rf.raw & 0xffffffffffff) == 0x555555555555);

        rf.node_id = 0xbeef;
        rf.protection_domain = 0xbabe;
        rf.vpid = 0x2ad;
        rf.mode = 0x37;

        REQUIRE((rf.raw & 0xffffffffffff) == 0xdeadbabebeef);
    }
}
TEST_CASE("Generated definition 'TraceRingbufferStart'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceRingbufferStart rf;

        rf.raw = 0x0;

        CHECK(rf.address == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.address == 0xffffffffffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.address == 0xaaaaaaaaaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.address == 0x5555555555555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.address == 0xcafedeadbabebeef);
    }

    SECTION("write fields - read raw")
    {
        TraceRingbufferStart rf;

        rf.address = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.address = 0xffffffffffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.address = 0xaaaaaaaaaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.address = 0x5555555555555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.address = 0xcafedeadbabebeef;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'TraceRingbufferCapacity'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceRingbufferCapacity rf;

        rf.raw = 0x0;

        CHECK(rf.capacity == 0x0);
        CHECK(rf.start_change_counter == 0x0);
        CHECK(rf.capacity_change_counter == 0x0);
        CHECK(rf.init == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.capacity == 0xffffffff);
        CHECK(rf.start_change_counter == 0xff);
        CHECK(rf.capacity_change_counter == 0xff);
        CHECK(rf.init == 0x1);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.capacity == 0xaaaaaaaa);
        CHECK(rf.start_change_counter == 0xaa);
        CHECK(rf.capacity_change_counter == 0xaa);
        CHECK(rf.init == 0x0);

        rf.raw = 0x5555555555555555;

        CHECK(rf.capacity == 0x55555555);
        CHECK(rf.start_change_counter == 0x55);
        CHECK(rf.capacity_change_counter == 0x55);
        CHECK(rf.init == 0x1);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.capacity == 0xbabebeef);
        CHECK(rf.start_change_counter == 0xad);
        CHECK(rf.capacity_change_counter == 0xde);
        CHECK(rf.init == 0x0);
    }

    SECTION("write fields - read raw")
    {
        TraceRingbufferCapacity rf;

        rf.capacity = 0x0;
        rf.start_change_counter = 0x0;
        rf.capacity_change_counter = 0x0;
        rf.init = 0x0;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0x0);

        rf.capacity = 0xffffffff;
        rf.start_change_counter = 0xff;
        rf.capacity_change_counter = 0xff;
        rf.init = 0x1;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0x1ffffffffffff);

        rf.capacity = 0xaaaaaaaa;
        rf.start_change_counter = 0xaa;
        rf.capacity_change_counter = 0xaa;
        rf.init = 0x0;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0xaaaaaaaaaaaa);

        rf.capacity = 0x55555555;
        rf.start_change_counter = 0x55;
        rf.capacity_change_counter = 0x55;
        rf.init = 0x1;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0x1555555555555);

        rf.capacity = 0xbabebeef;
        rf.start_change_counter = 0xad;
        rf.capacity_change_counter = 0xde;
        rf.init = 0x0;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0xdeadbabebeef);
    }
}
TEST_CASE("Generated definition 'ConfigResponse'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        ConfigResponse rf;

        rf.raw = 0x0;

        CHECK(rf.address == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.address == 0xffffffffffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.address == 0xaaaaaaaaaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.address == 0x5555555555555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.address == 0xcafedeadbabebeef);
    }

    SECTION("write fields - read raw")
    {
        ConfigResponse rf;

        rf.address = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.address = 0xffffffffffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.address = 0xaaaaaaaaaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.address = 0x5555555555555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.address = 0xcafedeadbabebeef;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'HicannRingbufferStart'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannRingbufferStart rf;

        rf.raw = 0x0;

        CHECK(rf.address == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.address == 0xffffffffffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.address == 0xaaaaaaaaaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.address == 0x5555555555555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.address == 0xcafedeadbabebeef);
    }

    SECTION("write fields - read raw")
    {
        HicannRingbufferStart rf;

        rf.address = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.address = 0xffffffffffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.address = 0xaaaaaaaaaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.address = 0x5555555555555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.address = 0xcafedeadbabebeef;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'HicannRingbufferCapacity'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannRingbufferCapacity rf;

        rf.raw = 0x0;

        CHECK(rf.capacity == 0x0);
        CHECK(rf.start_change_counter == 0x0);
        CHECK(rf.capacity_change_counter == 0x0);
        CHECK(rf.init == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.capacity == 0xffffffff);
        CHECK(rf.start_change_counter == 0xff);
        CHECK(rf.capacity_change_counter == 0xff);
        CHECK(rf.init == 0x1);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.capacity == 0xaaaaaaaa);
        CHECK(rf.start_change_counter == 0xaa);
        CHECK(rf.capacity_change_counter == 0xaa);
        CHECK(rf.init == 0x0);

        rf.raw = 0x5555555555555555;

        CHECK(rf.capacity == 0x55555555);
        CHECK(rf.start_change_counter == 0x55);
        CHECK(rf.capacity_change_counter == 0x55);
        CHECK(rf.init == 0x1);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.capacity == 0xbabebeef);
        CHECK(rf.start_change_counter == 0xad);
        CHECK(rf.capacity_change_counter == 0xde);
        CHECK(rf.init == 0x0);
    }

    SECTION("write fields - read raw")
    {
        HicannRingbufferCapacity rf;

        rf.capacity = 0x0;
        rf.start_change_counter = 0x0;
        rf.capacity_change_counter = 0x0;
        rf.init = 0x0;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0x0);

        rf.capacity = 0xffffffff;
        rf.start_change_counter = 0xff;
        rf.capacity_change_counter = 0xff;
        rf.init = 0x1;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0x1ffffffffffff);

        rf.capacity = 0xaaaaaaaa;
        rf.start_change_counter = 0xaa;
        rf.capacity_change_counter = 0xaa;
        rf.init = 0x0;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0xaaaaaaaaaaaa);

        rf.capacity = 0x55555555;
        rf.start_change_counter = 0x55;
        rf.capacity_change_counter = 0x55;
        rf.init = 0x1;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0x1555555555555);

        rf.capacity = 0xbabebeef;
        rf.start_change_counter = 0xad;
        rf.capacity_change_counter = 0xde;
        rf.init = 0x0;

        REQUIRE((rf.raw & 0x1ffffffffffff) == 0xdeadbabebeef);
    }
}
TEST_CASE("Generated definition 'TraceNotificationBehaviour'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        TraceNotificationBehaviour rf;

        rf.raw = 0x0;

        CHECK(rf.timeout == 0x0);
        CHECK(rf.frequency == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.timeout == 0xffffffff);
        CHECK(rf.frequency == 0xffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.timeout == 0xaaaaaaaa);
        CHECK(rf.frequency == 0xaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.timeout == 0x55555555);
        CHECK(rf.frequency == 0x55555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.timeout == 0xbabebeef);
        CHECK(rf.frequency == 0xcafedead);
    }

    SECTION("write fields - read raw")
    {
        TraceNotificationBehaviour rf;

        rf.timeout = 0x0;
        rf.frequency = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.timeout = 0xffffffff;
        rf.frequency = 0xffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.timeout = 0xaaaaaaaa;
        rf.frequency = 0xaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.timeout = 0x55555555;
        rf.frequency = 0x55555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.timeout = 0xbabebeef;
        rf.frequency = 0xcafedead;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'HicannNotificationBehaviour'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        HicannNotificationBehaviour rf;

        rf.raw = 0x0;

        CHECK(rf.timeout == 0x0);
        CHECK(rf.frequency == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.timeout == 0xffffffff);
        CHECK(rf.frequency == 0xffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.timeout == 0xaaaaaaaa);
        CHECK(rf.frequency == 0xaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.timeout == 0x55555555);
        CHECK(rf.frequency == 0x55555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.timeout == 0xbabebeef);
        CHECK(rf.frequency == 0xcafedead);
    }

    SECTION("write fields - read raw")
    {
        HicannNotificationBehaviour rf;

        rf.timeout = 0x0;
        rf.frequency = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.timeout = 0xffffffff;
        rf.frequency = 0xffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.timeout = 0xaaaaaaaa;
        rf.frequency = 0xaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.timeout = 0x55555555;
        rf.frequency = 0x55555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.timeout = 0xbabebeef;
        rf.frequency = 0xcafedead;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'Driver'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        Driver rf;

        rf.raw = 0x0;

        CHECK(rf.version == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.version == 0xffffffffffffffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.version == 0xaaaaaaaaaaaaaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.version == 0x5555555555555555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.version == 0xcafedeadbabebeef);
    }

    SECTION("write fields - read raw")
    {
        Driver rf;

        rf.version = 0x0;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x0);

        rf.version = 0xffffffffffffffff;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xffffffffffffffff);

        rf.version = 0xaaaaaaaaaaaaaaaa;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xaaaaaaaaaaaaaaaa);

        rf.version = 0x5555555555555555;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0x5555555555555555);

        rf.version = 0xcafedeadbabebeef;

        REQUIRE((rf.raw & 0xffffffffffffffff) == 0xcafedeadbabebeef);
    }
}
TEST_CASE("Generated definition 'Info'", "[definitions]")
{
    SECTION("write raw - read fields")
    {
        Info rf;

        rf.raw = 0x0;

        CHECK(rf.guid == 0x0);
        CHECK(rf.node_id == 0x0);

        rf.raw = 0xffffffffffffffff;

        CHECK(rf.guid == 0xffffff);
        CHECK(rf.node_id == 0xffff);

        rf.raw = 0xaaaaaaaaaaaaaaaa;

        CHECK(rf.guid == 0xaaaaaa);
        CHECK(rf.node_id == 0xaaaa);

        rf.raw = 0x5555555555555555;

        CHECK(rf.guid == 0x555555);
        CHECK(rf.node_id == 0x5555);

        rf.raw = 0xcafedeadbabebeef;

        CHECK(rf.guid == 0xbebeef);
        CHECK(rf.node_id == 0xadba);
    }

    SECTION("write fields - read raw")
    {
        Info rf;

        rf.guid = 0x0;
        rf.node_id = 0x0;

        REQUIRE((rf.raw & 0xffffffffff) == 0x0);

        rf.guid = 0xffffff;
        rf.node_id = 0xffff;

        REQUIRE((rf.raw & 0xffffffffff) == 0xffffffffff);

        rf.guid = 0xaaaaaa;
        rf.node_id = 0xaaaa;

        REQUIRE((rf.raw & 0xffffffffff) == 0xaaaaaaaaaa);

        rf.guid = 0x555555;
        rf.node_id = 0x5555;

        REQUIRE((rf.raw & 0xffffffffff) == 0x5555555555);

        rf.guid = 0xbebeef;
        rf.node_id = 0xadba;

        REQUIRE((rf.raw & 0xffffffffff) == 0xadbabebeef);
    }
}
