#ifndef BLOCK_H
#define BLOCK_H

#include <cassert>

#include "fixedparam.h"
#include "types.h"

struct Block : FixedBlockParam<4,2>
{
    Block();
    Block(uint64_t);
    Block(const Block& other);
    Block(Block&&) = delete;
    bool IsZero() const;
    void Print() const;
    byte&  operator [] (unsigned i);
    Block& operator =  (uint64_t num);
    Block& operator =  (const Block& other);
    Block& operator &= (const Block& other);
    Block& operator ++ ();
    Block& operator ^= (const Block& other);
    bool operator == (const Block& other);
    operator bool() const { return !IsZero(); }

private:
    byte subs[NUMSUBBLOCKS];
};
struct Transform
{
    void ProcessBlock(Block &block) {}
};

#endif
