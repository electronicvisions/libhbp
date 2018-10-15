#ifndef LIBHBP_CPP_HICANN_H
#define LIBHBP_CPP_HICANN_H

#include <connection.h>

class Hicann
{
private:
    Connection& connection;
public:
    explicit Hicann(Connection&);
};


#endif //LIBHBP_CPP_HICANN_H
