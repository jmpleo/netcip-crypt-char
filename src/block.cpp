#include "block.h"


#include <iostream>

void Block::Print() const
{
    std::cout << '(';
    for (unsigned int i = 0; i < FixedBlockParam::NUMSUBBLOCKS - 1; ++i) {
        std::cout << (int)subs[i] << ", ";
    }
    std::cout << (int)subs[FixedBlockParam::NUMSUBBLOCKS-1] << ")\n";
}


bool Block::IsZero() const
{
    for (unsigned int i = 0; i < FixedBlockParam::NUMSUBBLOCKS; ++i) {
        if (subs[i]) {
            return false;
        }
    }
    return true;
}


Block::Block()
{
    for(unsigned int i = 0; i < FixedBlockParam::NUMSUBBLOCKS; ++i) {
        subs[i] = 0;
    }
}


Block::Block(uint64_t a)
{
    *this = a;
}


Block& Block::operator=(uint64_t a)
{
    for (unsigned int i = 0; i < FixedBlockParam::NUMSUBBLOCKS; ++i) {
        subs[i] = (byte)(
            a >> (
                FixedBlockParam::SUBBLOCKSIZE
                * (FixedBlockParam::NUMSUBBLOCKS - i - 1)
            )
        ) & (0xFF >> (8 - FixedBlockParam::SUBBLOCKSIZE));
    }
    return *this;
}


uint8_t& Block::operator [] (unsigned int i)
{
    return subs[i];
}


Block& Block::operator &= (Block const & other)
{
    for (unsigned int i = 0; i < FixedBlockParam::NUMSUBBLOCKS; ++i) {
        subs[i] &= other.subs[i];
    }
    return *this;
}


Block& Block::operator++()
{
    for (unsigned int i = 0; i < FixedBlockParam::NUMSUBBLOCKS; ++i) {
        ++subs[FixedBlockParam::NUMSUBBLOCKS - 1 - i];
        if (subs[FixedBlockParam::NUMSUBBLOCKS - 1 - i]
                &= (0x00FF >> (8 - FixedBlockParam::SUBBLOCKSIZE))) {
            break;
        }
    }
    return *this;
}


Block::Block(const Block& other)
{
    if (&other != this) {
        *this = other;
    }
}


Block& Block::operator=(const Block& other)
{
    for (int i = 0; i < FixedBlockParam::NUMSUBBLOCKS; ++i) {
        subs[i] = other.subs[i];
    }
    return *this;
}


Block& Block::operator^=(const Block& other)
{
    for (int i = 0; i < FixedBlockParam::NUMSUBBLOCKS; ++i) {
        subs[i] = subs[i] ^ other.subs[i];
    }
    return *this;
}


bool Block::operator==(const Block& other)
{
    for (int i = 0; i < FixedBlockParam::NUMSUBBLOCKS; ++i) {
        if (subs[i] != other.subs[i]) {
            return false;
        }
    }
    return true;
}
