	bool DNC_start_link(unsigned short wdata) override ;
	bool DNC_stop_link(unsigned short wdata) override ;
	bool DNC_set_channel(unsigned char wdata) override ;
	bool DNC_set_tx_data(uint64_t wdata) override ;
	template <typename T>
	bool DNC_get_rx_data(T& rdata) override ;
	{
		throw std::runtime_error("Deprecated: DNC_get_rx_data");
	}

	bool DNC_lvds_pads_en(unsigned short wdata) override ;
	bool DNC_set_loopback(unsigned char wdata) override ;
	bool DNC_set_l1direction(uint64_t wdata) override ;
	bool DNC_write_routing_dat(void) override ;
	bool DNC_set_GHz_pll_ctrl(unsigned char wdata) override ;
	bool DNC_start_cfg_pkg(void) override ;
	bool DNC_start_pulse_pkg(void) override ;
	bool DNC_read_status(uint64_t& rdata) override ;
	bool DNC_read_channel_sts(unsigned char channel, unsigned char& status) override ;
	template <typename T>
	bool DNC_read_crc_count(T& rdata) override ;
	{
		throw std::runtime_error("Deprecated: DNC_read_crc_count");
	}

	bool DNC_reset_crc_count(unsigned char wdata) override ;
	template <typename T>
	bool DNC_read_heap_count(T& rdata) override ;
	{
		throw std::runtime_error("Deprecated: DNC_read_heap_count");
	}

	bool DNC_reset_heap_count(uint64_t wdata) override ;
	bool DNC_set_reset(unsigned char wdata) override ;
	bool DNC_set_pulse_protocol(unsigned char wdata) override ;
	bool DNC_set_bias_bypass(unsigned char wdata) override ;
	bool DNC_set_memory_test_mode(unsigned char wdata) override ;
	bool DNC_set_config_protocol(unsigned char wdata) override ;
	bool DNC_set_time_limit(unsigned char wdata) override ;
	bool DNC_set_timestamp_ctrl(unsigned char wdata) override ;
	bool DNC_set_lowspeed_ctrl(unsigned char wdata) override ;
	bool DNC_set_speed_detect_ctrl(unsigned char wdata) override ;
	bool DNC_set_dc_coding_ctrl(unsigned char wdata) override ;
	bool DNC_test_mode_en(void) override ;
	bool DNC_test_mode_dis(void) override ;
	bool DNC_set_data_delay(const std::vector<bool>& wdata, std::vector<bool>& rdata) override ;
	template <typename T>
	bool bypass(const T wdata, unsigned int length, T& rdata) override ;
	{
		throw std::runtime_error("Not Implemented: bypass");
	}

	bool DNC_start_pulse(unsigned char channel, uint64_t data) override ;
	bool DNC_start_config(unsigned char channel, uint64_t data) override ;
	bool DNC_start_routing(unsigned char channel, uint64_t data) override ;
	bool DNC_set_init_ctrl(unsigned int wdata) override ;
	bool DNC_set_test_lvds_ctrl(unsigned short wdata) override ;
	bool read_id(uint64_t& rdata, unsigned char chip_nr) override ;
	uint64_t read_id(unsigned char chip_nr) override ;
	bool HICANN_chip_reset(void) override ;
	bool HICANN_set_if_reset(void) override ;
	bool HICANN_rel_if_reset(void) override ;
	bool HICANN_lvds_pads_en(unsigned short wdata) override ;
	bool HICANN_start_link() override ;
	bool HICANN_stop_link() override ;
	bool HICANN_set_pls64(unsigned char wdata) override ;
	bool HICANN_start_cfg_pkg() override ;
	bool HICANN_start_pulse_pkg() override ;
	template <typename T>
	bool HICANN_read_status(T& rdata) override ;
	{
		auto jtag = extoll->jtag(node);
		
		return true;
	}

	template <typename T>
	bool HICANN_read_crc_count(T& count) override ;
	{
		auto jtag = extoll->jtag(node);
		
		return true;
	}

	bool HICANN_reset_crc_count() override ;
	bool HICANN_start_time_counter() override ;
	bool HICANN_stop_time_counter() override ;
	bool HICANN_reset_all_time_counters() override ;
	bool HICANNv2_reset_all_time_counters() override ;
	bool HICANN_restart_time_counter() override ;
	bool HICANN_set_tx_data(uint64_t wdata) override ;
	bool HICANN_get_rx_data(uint64_t& rdata) override ;
	template <typename T>
	bool HICANN_read_systime(T& rdata) override ;
	{
		auto jtag = extoll->jtag(node);
		
		return true;
	}

	bool FPGA_start_dnc_packet(unsigned short wdata) override ;
	bool FPGA_set_channel(unsigned int wdata) override ;
	bool FPGA_testmode(unsigned int wdata) override ;
	bool HICANN_set_GHz_pll_ctrl(unsigned char wdata) override ;
	bool hicannif_nrn0_filter_ctrl(unsigned char wdata) override ;
	bool FPGA_set_fpga_ctrl(unsigned short wdata) override ;
	bool FPGA_set_tx_data(uint64_t wdata) override ;
	bool FPGA_set_systime_ctrl(uint64_t wdata) override ;
	bool FPGA_get_status(uint64_t& rdata) override ;
	bool FPGA_get_crc(unsigned char& rdata) override ;
	template <typename T>
	bool FPGA_get_rx_channel(T& rdata) override ;
	{
		throw std::runtime_error("Not Implemented: FPGA_get_rx_channel");
	}

	template <typename T>
	bool FPGA_get_rx_data(T& rdata) override ;
	{
		throw std::runtime_error("Not Implemented: FPGA_get_rx_data");
	}

	bool FPGA_set_cont_pulse_ctrl( override ;
	bool FPGA_start_pulse_event(unsigned char channel, uint64_t wdata) override ;
	bool FPGA_start_config_packet(unsigned char channel, uint64_t wdata) override ;
	bool FPGA_cfg_dnc_l1direction(unsigned char channel, uint64_t wdata) override ;
	bool FPGA_write_playback_fifo(uint64_t wdata) override ;
	bool FPGA_enable_pulsefifo() override ;
	bool FPGA_disable_pulsefifo() override ;
	bool FPGA_enable_tracefifo() override ;
	bool FPGA_disable_tracefifo() override ;
	bool FPGA_enable_filter_tracefifo() override ;
	bool FPGA_disable_filter_tracefifo() override ;
	bool FPGA_enable_fifoloop() override ;
	bool FPGA_disable_fifoloop() override ;
	template <typename T>
	bool FPGA_get_trace_fifo(unsigned int& systime, T& rdata) override ;
	{
		throw std::runtime_error("Not Implemented: FPGA_get_trace_fifo");
	}

	template <typename T>
	bool FPGA_get_trace_fifo(T& rdata) override ;
	{
		throw std::runtime_error("Not Implemented: FPGA_get_trace_fifo");
	}

	template <typename T>
	bool FPGA_get_trace_fifo(T& rdata, bool& is_config_packet) override ;
	{
		throw std::runtime_error("Not Implemented: FPGA_get_trace_fifo");
	}

	bool FPGA_reset_tracefifo() override ;
	template <typename T>
	bool FPGA_get_rx_packet(uint64_t channel, T& rdata) override ;
	{
		throw std::runtime_error("Not Implemented: FPGA_get_rx_packet");
	}

	bool FPGA_empty_pulsefifo() override ;
