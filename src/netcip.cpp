#include "netcip.h"
#include "net.h"


void Enc::ProcessBlock ( byte* block )
{
    #define R1(i) (block[i + 1] = encTab_ \
        [ block[i] ][ block[i + 1] ] \
    )

    #define C(i, j) (block[j] = encTab_ \
        [ block[i] ][ block[j] ] \
    )

    #define L1(i) (block[i - 1] = encTab_ \
        [ block[i] ][ block[i - 1] ] \
    )

    R1(0); R1(1); R1(2); R1(3); R1(4); R1(5); R1(6);
    C(7, 0);
    R1(6); R1(5); R1(4); R1(3); R1(2); R1(1); L1(2);

    #undef R1
    #undef C
    #undef L1
}

void Dec::ProcessBlock ( byte* block )
{
    #define R1(i) (block[i] = decTab_ \
        [ block[i + 1] ][ block[i] ] \
    )

    #define C(i, j) (block[j] = decTab_ \
        [ block[i] ][ block[j] ] \
    )

    #define L1(i) (block[i] = decTab_ \
        [ block[i - 1] ][ block[i] ] \
    )

    R1(1); L1(2); L1(3); L1(4); L1(5); L1(6); L1(7);
    C(0, 7);
    L1(7); L1(6); L1(5); L1(4); L1(3); L1(2); L1(1);

    #undef R1
    #undef C
    #undef L1
}


void Enc::ProcessBlock ( Block &block )
{
    for (unsigned int i = 1; i < Network::ROUNDS; ++i) {
        block[ net_[i] ]
            = encTab_[ block[ net_[i-1] ] ] // first arg
                     [ block[ net_[i  ] ] ];// second arg
    }
}

void Dec::ProcessBlock( Block &block )
{
    for (unsigned int i = Network::ROUNDS - 1; i > 0; --i) {
        block[ net_[i] ]
            = decTab_[ block[ net_[i-1] ] ] // first arg
                     [ block[ net_[i  ] ] ];// second arg
    }
}

