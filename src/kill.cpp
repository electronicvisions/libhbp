#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <rma2.h>
#pragma GCC diagnostic pop


int main()
{
	RMA2_Port port = nullptr;
	rma2_open(&port);

	RMA2_VPID vpid = RMA2_VPID_ANY;
	RMA2_Handle handle;
	rma2_connect(port, 2, vpid, RMA2_CONN_RRA, &handle);

	for (int i = 0; i < 1000000; ++i) {
		rma2_post_immediate_put(
		    port, handle, 8, 0xdead, 0x400, RMA2_ALL_NOTIFICATIONS, RMA2_CMD_DEFAULT);
	}
}
