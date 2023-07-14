#ifndef NET_H
#define NET_H

#include "block.h"
#include "config.h"

class Network : public Block,
                public FixedRounds<_H>
{
public:
    Network()
    {
        for (unsigned int i = 0; i < FixedRounds::ROUNDS; ++i) {
            net_[i] = i % Block::NUMSUBBLOCKS;
        }
    }
protected:
    unsigned int net_[FixedRounds::ROUNDS];
};

#endif
