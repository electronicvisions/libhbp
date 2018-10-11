#include <fpga.h>

#include "fpga.h"

using namespace rf;

void Fpga::reset()
{
    RegisterFile::write<Reset>({true, true, true});
    RegisterFile::write<Reset>({false, false, false});
}

void Fpga::configure_partner_host()
{
    const static uint32_t default_timeout = 125000;
    const static uint32_t default_frequency = (1024 * 4 / 512 - 5);

    RMA2_Nodeid local_node = rma2_get_nodeid(connection.port);
    write_noblock<HostEndpoint>({local_node, connection.vpid, 0, 1 << 2});
    write_noblock<TraceRingbufferStart>({connection.trace_data.address()});
    write_noblock<TraceRingbufferCapacity>({connection.trace_data.byte_size(), true});
    write_noblock<ConfigResponse>({connection.gp_buffer.address() + 512});
    write_noblock<HicannRingbufferStart>({connection.hicann_config.address()});
    write_noblock<HicannRingbufferCapacity>({connection.hicann_config.byte_size(), true});
    write_noblock<TraceNotificationBehaviour>({default_timeout, default_frequency});
    write_noblock<HicannNotificationBehaviour>({default_timeout, default_frequency});

    wait_for_n_notifications(8);
}
