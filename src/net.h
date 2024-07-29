#ifndef NET_H
#define NET_H

#include "block.h"
#include "config.h"

class Network : public Block , public FixedRounds<_H>
{
public:
    Network()
    {
        for (unsigned int i = 0; i < ROUNDS; ++i) net_[i] = i % NUMSUBBLOCKS;
    }

protected:
    unsigned int net_[ROUNDS];
};

#endif
