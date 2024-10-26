#include "netcip.h"
#include "net.h"



void Enc::operator() ( Block &block )
{
    for (unsigned int i = 1; i < Network::ROUNDS; ++i) {
        block[ net_[i] ]
            = encTab_[ block[ net_[i-1] ] ] // first arg
                     [ block[ net_[i  ] ] ];// second arg
    }
}

void Dec::operator()( Block &block )
{
    for (unsigned int i = Network::ROUNDS - 1; i > 0; --i) {
        block[ net_[i] ]
            = decTab_[ block[ net_[i-1] ] ] // first arg
                     [ block[ net_[i  ] ] ];// second arg
    }
}

