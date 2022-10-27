#ifndef BLOCK_H
#define BLOCK_H

#include <cassert>

#include "types.h"

template <unsigned int N, unsigned int M>
struct FixedBlockParam
{
    static const int SUBBLOCKSIZE = N;
    static const int NUMSUBBLOCKS = M;
};
template <unsigned int S>
struct FixedBlockSize
{
    static const int BLOCKSIZE = S;
};
template <unsigned int R>
struct FixedRounds
{
    static const int ROUNDS = R;
};
struct Block : FixedBlockParam<3,4>
{
    Block();
    Block(uint64_t);
    bool IsZero() const;
    void Print() const;
    byte&  operator [] (unsigned i);
    Block& operator =  (uint64_t num);
    Block& operator &= (const Block& other);
    Block& operator ++ ();
private:
    byte subs[NUMSUBBLOCKS];
};
struct Transform
{
    virtual void ProcessBlock(Block &block) = 0;
};
#endif
