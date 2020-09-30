#ifndef LIBHBP_CPP_HELPER_H
#define LIBHBP_CPP_HELPER_H

#include <sstream>

#include <extoll/rma.h>

namespace extoll {
namespace library {

template <typename E, typename... Args>
void throw_on_error(RMA2_ERROR status, Args... args)
{
	if (status != RMA2_SUCCESS) {
		throw E(args...);
	}
}

}
}

#endif // LIBHBP_CPP_HELPER_H
