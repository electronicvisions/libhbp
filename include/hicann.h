#ifndef LIBHBP_CPP_HICANN_H
#define LIBHBP_CPP_HICANN_H

#include <connection.h>

class Hicann
{
private:
    Endpoint& connection;
public:
    explicit Hicann(Endpoint&);
};


#endif //LIBHBP_CPP_HICANN_H
