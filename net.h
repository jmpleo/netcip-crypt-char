#ifndef NET_H
#define NET_H

#include "block.h"

class Network : public Block,
                public FixedRounds<8>
{
public:
    Network()
    {
        for (unsigned int i = 0; i < ROUNDS; ++i) {
            net_[i] = i % NUMSUBBLOCKS;
        }
    }
protected:
    unsigned int net_[ROUNDS];
};

#endif
