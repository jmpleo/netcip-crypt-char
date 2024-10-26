#include "lin-comb.h"
#include "block.h"

#include <memory.h>
#include <vector>

/*
 * for each x=x_1x_2...x_nm and coef=c_1c_2...c_nm
 * linComb[x] = (f_1(x) & c_1) ^ ... ^ (f_nm(x) & c_nm)
 * then you can linComb[x] (is a Block) cast to bool,
 * so linComb using as "bool_vec" (bool function)
 */
void LinearCombination( std::vector<Block> const & funcSet,
                        std::vector<bool> & linearComb,
                        Block &coef )
{
    Block block;

    for (std::uint64_t bitNum, k, x = 0; x < funcSet.size(); ++x) {

        bool bit = 0;

        for (k = 0; k < Block::NUM_SUBBLOCKS; ++k) {

            block[k] = funcSet[x][k] & coef[k];

            for (bitNum = 0; bitNum < Block::SUBBLOCK_SIZE; ++bitNum) {
                bit ^= ((block[k] >> bitNum) & 1);
            }
        }

        linearComb[x] = bit;
    }
}

