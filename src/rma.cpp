#include <rma.h>


void wait_for_notification(RMA2_Port port)
{
    RMA2_Notification* notification;
    rma2_noti_get_block(port, &notification);
    rma2_noti_free(port, notification);
}

void wait_for_n_notifications(RMA2_Port port, int n)
{
    RMA2_Notification* notification;

    for (int i = 0; i < n; ++i)
    {
        rma2_noti_get_block(port, &notification);
        rma2_noti_free(port, notification);
    }
}