#ifndef NET_H
#define NET_H

#include "block.h"
#include "config.h"
#include <string>

class Network : public FixedRounds<_H>
{
public:
    Network() {
        for (unsigned int i = 0; i < ROUNDS; ++i) net_[i] = i % Block::NUMSUBBLOCKS;
    }

    std::string HexNet () {
        std::string seq;
        for (auto &l : net_) {
            seq += std::to_string(l);
            seq += '-';
        }
        return seq.pop_back(), seq;
    }

protected:
    unsigned int net_[ROUNDS];
};

#endif
