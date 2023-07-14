#include "netcip.h"

/*
 * NOTE: Implementation transformition for experiment.
 *       In application use implementation:
 *
 * void NetCip::Enc::ProcessBlock ( byte* block )
 * {
 *      // define one round:
 *      #define N(l,s) ( block[j] = _encTab[ block[l] ][ block[s] ] )
 *
 *      // and weave a your network:
 *      // NOTE: You need keep M so that it does not get out of the block
 *      N(0,1); N(1,2); N(2,3); // ...
 * }
 *
 * void NetCip::Dec::ProcessBlock ( byte* block )
 * {
 *      #define N(l,s) ( block[j] = _decTab[ block[l] ][ block[s] ] )
 *
 *      // reverse you network:
 *      N(2,3); N(1,2); N(0,1); // ...
 * }
 *
 */
void NetCip::Enc::ProcessBlock ( Block &block )
{
    for (unsigned int i = 1; i < NetCip::Param::ROUNDS; ++i) {
        block[ net_[i] ]
            = encTab_[ block[ net_[i-1] ] ] // first arg
                     [ block[ net_[i  ] ] ];// second arg
    }
}

void NetCip::Dec::ProcessBlock( Block &block )
{
    for (unsigned int i = NetCip::Param::ROUNDS - 1; i > 0; --i) {
        block[ net_[i] ]
            = decTab_[ block[ net_[i-1] ] ] // first arg
                     [ block[ net_[i  ] ] ];// second arg
    }
}

