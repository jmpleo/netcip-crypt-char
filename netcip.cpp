#include "netcip.h"

void NetCip::Enc::ProcessBlock(Block &block)
{
    for (unsigned int i = 1; i < ROUNDS; ++i) {
        block[ net_[i] ]
            = encTab_[ block[ net_[i-1] ] ] // first arg
                     [ block[ net_[i  ] ] ];// second arg
    }
}
void NetCip::Dec::ProcessBlock(Block &block)
{
    for (unsigned int i = ROUNDS - 1; i > 0; --i) {
        block[ net_[i] ]
            = decTab_[ block[ net_[i-1] ] ] // first arg
                     [ block[ net_[i  ] ] ];// second arg
    }
}

