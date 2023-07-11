#include "lin-comb.h"

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
    static uint64_t val, k, j, i,
        numSubs = Block::NUMSUBBLOCKS,
        subSize = Block::SUBBLOCKSIZE,
        bitSize = numSubs * subSize,
        funcLen = (1 << bitSize);
    std::copy(source.begin(), source.end(), dest.begin());
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

