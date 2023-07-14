#include "lin-comb.h"
#include "block.h"
#include "types.h"

#include <algorithm>
#include <memory.h>
#include <vector>

/*
 * for each x=x_1x_2...x_nm and coef=c_1c_2...c_nm
 * linComb[x] = (f_1(x) & c_1) ^ ... ^ (f_nm(x) & c_nm)
 * then you can linComb[x] (is a Block) cast to bool,
 * so linComb using as "bool_vec" (bool function)
 */
void LinearCombination( std::vector<Block> &source,
                        std::vector<Block> &dest,
                        Block &coef )
{
    std::copy(source.begin(), source.end(), dest.begin());
    static uint64_t bitValue, k, bitNum, x,
        blockSizeInBit = Block::NUMSUBBLOCKS * Block::SUBBLOCKSIZE,
        funcLen = (1ULL << blockSizeInBit);
    for (x = 0; x < funcLen; ++x) {
        dest[x] &= coef;
        bitValue = 0;
        for (k = 0; k < Block::NUMSUBBLOCKS; ++k) {
            for (bitNum = 0; bitNum < blockSizeInBit; ++bitNum) {
                bitValue ^= (dest[x][k] >> bitNum) & 0x1;
            }
        }
        dest[x] = bitValue;
    }
}

