#pragma once

#include <cassert>
#include <vector>

#include "config.h"
#include "fixedparam.h"
#include "types.h"

/*
 * Class of block intended for various configuration transformition
 *
 * NOTE: Do not use this class for application cipher - use byte arr
 */
struct Block : FixedBlockParam <_N,_M>
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
    Block& operator ^= (const Block& other);
    Block& operator ++ ();
    bool   operator == (const Block& other);
    bool   operator != (const Block& other) { return ! (*this == other); }
           operator bool() const { return !IsZero(); }

    static bool_vec ToBoolFunc(const std::vector<Block> &blockSet);
private:
    byte subs[FixedBlockParam::NUMSUBBLOCKS];
};

