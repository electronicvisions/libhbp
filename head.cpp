bool DNC_start_link(unsigned short wdata)
{
	throw std::runtime_error("Deprecated: DNC_start_link");
}

bool DNC_stop_link(unsigned short wdata)
{
	throw std::runtime_error("Deprecated: DNC_stop_link");
}

bool DNC_set_channel(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_channel");
}

bool DNC_set_tx_data(uint64_t wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_tx_data");
}

bool DNC_lvds_pads_en(unsigned short wdata)
{
	throw std::runtime_error("Deprecated: DNC_lvds_pads_en");
}

bool DNC_set_loopback(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_loopback");
}

bool DNC_set_l1direction(uint64_t wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_l1direction");
}

bool DNC_write_routing_dat(void)
{
	throw std::runtime_error("Deprecated: DNC_write_routing_dat");
}

bool DNC_set_GHz_pll_ctrl(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_GHz_pll_ctrl");
}

bool DNC_start_cfg_pkg(void)
{
	throw std::runtime_error("Deprecated: DNC_start_cfg_pkg");
}

bool DNC_start_pulse_pkg(void)
{
	throw std::runtime_error("Deprecated: DNC_start_pulse_pkg");
}

bool DNC_read_status(uint64_t& rdata)
{
	throw std::runtime_error("Deprecated: DNC_read_status");
}

bool DNC_read_channel_sts(unsigned char channel, unsigned char& status)
{
	throw std::runtime_error("Deprecated: DNC_read_channel_sts");
}

bool DNC_reset_crc_count(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_reset_crc_count");
}

bool DNC_reset_heap_count(uint64_t wdata)
{
	throw std::runtime_error("Deprecated: DNC_reset_heap_count");
}

bool DNC_set_reset(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_reset");
}

bool DNC_set_pulse_protocol(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_pulse_protocol");
}

bool DNC_set_bias_bypass(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_bias_bypass");
}

bool DNC_set_memory_test_mode(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_memory_test_mode");
}

bool DNC_set_config_protocol(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_config_protocol");
}

bool DNC_set_time_limit(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_time_limit");
}

bool DNC_set_timestamp_ctrl(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_timestamp_ctrl");
}

bool DNC_set_lowspeed_ctrl(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_lowspeed_ctrl");
}

bool DNC_set_speed_detect_ctrl(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_speed_detect_ctrl");
}

bool DNC_set_dc_coding_ctrl(unsigned char wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_dc_coding_ctrl");
}

bool DNC_test_mode_en(void)
{
	throw std::runtime_error("Deprecated: DNC_test_mode_en");
}

bool DNC_test_mode_dis(void)
{
	throw std::runtime_error("Deprecated: DNC_test_mode_dis");
}

bool DNC_set_data_delay(const std::vector<bool>& wdata, std::vector<bool>& rdata)
{
	throw std::runtime_error("Deprecated: DNC_set_data_delay");
}

bool DNC_start_pulse(unsigned char channel, uint64_t data)
{
	throw std::runtime_error("Deprecated: DNC_start_pulse");
}

bool DNC_start_config(unsigned char channel, uint64_t data)
{
	throw std::runtime_error("Deprecated: DNC_start_config");
}

bool DNC_start_routing(unsigned char channel, uint64_t data)
{
	throw std::runtime_error("Deprecated: DNC_start_routing");
}

bool DNC_set_init_ctrl(unsigned int wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_init_ctrl");
}

bool DNC_set_test_lvds_ctrl(unsigned short wdata)
{
	throw std::runtime_error("Deprecated: DNC_set_test_lvds_ctrl");
}

bool read_id(uint64_t& rdata, unsigned char chip_nr)
{
	throw std::runtime_error("Not Implemented: read_id");
}

uint64_t read_id(unsigned char chip_nr)
{
	throw std::runtime_error("Not Implemented: read_id");
}

bool HICANN_chip_reset(void)
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_set_if_reset(void)
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_rel_if_reset(void)
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_lvds_pads_en(unsigned short wdata)
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_start_link()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_stop_link()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_set_pls64(unsigned char wdata)
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_start_cfg_pkg()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_start_pulse_pkg()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_reset_crc_count()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_start_time_counter()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_stop_time_counter()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_reset_all_time_counters()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANNv2_reset_all_time_counters()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_restart_time_counter()
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_set_tx_data(uint64_t wdata)
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool HICANN_get_rx_data(uint64_t& rdata)
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool FPGA_start_dnc_packet(unsigned short wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_start_dnc_packet");
}

bool FPGA_set_channel(unsigned int wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_set_channel");
}

bool FPGA_testmode(unsigned int wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_testmode");
}

bool HICANN_set_GHz_pll_ctrl(unsigned char wdata)
{
	auto jtag = extoll->jtag(node);
	
	return true;
}

bool hicannif_nrn0_filter_ctrl(unsigned char wdata)
{
	throw std::runtime_error("Not Implemented: hicannif_nrn0_filter_ctrl");
}

bool FPGA_set_fpga_ctrl(unsigned short wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_set_fpga_ctrl");
}

bool FPGA_set_tx_data(uint64_t wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_set_tx_data");
}

bool FPGA_set_systime_ctrl(uint64_t wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_set_systime_ctrl");
}

bool FPGA_get_status(uint64_t& rdata)
{
	throw std::runtime_error("Not Implemented: FPGA_get_status");
}

bool FPGA_get_crc(unsigned char& rdata)
{
	throw std::runtime_error("Not Implemented: FPGA_get_crc");
}

bool FPGA_set_cont_pulse_ctrl(
{
	throw std::runtime_error("Not Implemented: FPGA_set_cont_pulse_ctrl");
}

bool FPGA_start_pulse_event(unsigned char channel, uint64_t wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_start_pulse_event");
}

bool FPGA_start_config_packet(unsigned char channel, uint64_t wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_start_config_packet");
}

bool FPGA_cfg_dnc_l1direction(unsigned char channel, uint64_t wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_cfg_dnc_l1direction");
}

bool FPGA_write_playback_fifo(uint64_t wdata)
{
	throw std::runtime_error("Not Implemented: FPGA_write_playback_fifo");
}

bool FPGA_enable_pulsefifo()
{
	throw std::runtime_error("Not Implemented: FPGA_enable_pulsefifo");
}

bool FPGA_disable_pulsefifo()
{
	throw std::runtime_error("Not Implemented: FPGA_disable_pulsefifo");
}

bool FPGA_enable_tracefifo()
{
	throw std::runtime_error("Not Implemented: FPGA_enable_tracefifo");
}

bool FPGA_disable_tracefifo()
{
	throw std::runtime_error("Not Implemented: FPGA_disable_tracefifo");
}

bool FPGA_enable_filter_tracefifo()
{
	throw std::runtime_error("Not Implemented: FPGA_enable_filter_tracefifo");
}

bool FPGA_disable_filter_tracefifo()
{
	throw std::runtime_error("Not Implemented: FPGA_disable_filter_tracefifo");
}

bool FPGA_enable_fifoloop()
{
	throw std::runtime_error("Not Implemented: FPGA_enable_fifoloop");
}

bool FPGA_disable_fifoloop()
{
	throw std::runtime_error("Not Implemented: FPGA_disable_fifoloop");
}

bool FPGA_reset_tracefifo()
{
	throw std::runtime_error("Not Implemented: FPGA_reset_tracefifo");
}

bool FPGA_empty_pulsefifo()
{
	throw std::runtime_error("Not Implemented: FPGA_empty_pulsefifo");
}

