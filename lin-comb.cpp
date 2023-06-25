#include "lin-comb.h"

#include <algorithm>
#include <memory.h>

void LinearCombination(std::vector<Block> &source,
                       std::vector<Block> &dest,
                       Block & coef)
{
    static uint64_t val, k, j, i,
        numSubs = Block::NUMSUBBLOCKS,
        subSize = Block::SUBBLOCKSIZE,
        bitSize = numSubs * subSize,
        funcLen = (1 << bitSize);
    std::copy(source.begin(), source.end(), dest.begin());
    //memcpy(dest, source, sizeof(Block)*funcLen);
    for (i = 0; i < funcLen; ++i) {
        dest[i] &= coef;
        for (val = 0, k = 0; k < numSubs; ++k) {
            for (j = 0; j < bitSize; ++j) {
                val ^= (dest[i][k] >> j) & 1;
            }
        }
        dest[i] = val;
    }
}

