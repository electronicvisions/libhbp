#ifndef LIBHBP_CPP_RMA_H
#define LIBHBP_CPP_RMA_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <rma2.h>
#pragma GCC diagnostic pop

void wait_for_notification(RMA2_Port);
void wait_for_n_notifications(RMA2_Port, int);

#endif //LIBHBP_CPP_RMA_H
