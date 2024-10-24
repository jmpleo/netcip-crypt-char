#include "block.h"
#include "netcip.h"
#include "ai.h"
#include "lin-comb.h"
#include "progbar.h"

#include <cstdint>

#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>

#include <string>
#include <vector>

#include <cmath>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr<< "netstat-ai KEYS\n";
        return 1;
    }

    ProgressBar<> progbar;
    Enc enc;

    unsigned ai;

    std::uint64_t
        x,
        nKey,
        funcLen = (1ULL << Block::BLOCKSIZE),
        totalKeys = std::stoull(argv[1]);

    std::vector<Block> blockSet(funcLen);
    std::vector<bool> f(funcLen);

    for (nKey = 0; nKey < totalKeys; ++nKey) {

        progbar.Show(static_cast<float>(nKey) / totalKeys, std::cerr);

        ai = UINT16_MAX;

        enc.UpdateKey();

        // blockSet[...] is set of value coordinate functions of Enc()
        // where blockSet[x] = (f_1(x), f_2(x), ...,f_nm(x))
        // moreover, x=x_1x_2..x_nm ordered by lexicographic
        for (x = 0; x < funcLen; ++x) {
            blockSet[x] = x;
            enc(blockSet[x]);
        }

        for (Block coef{1}; !coef.IsZero(); ++coef) {

            // for each x=x_1x_2...x_nm and coef=c_1c_2...c_nm
            // linComb[x] = (f_1(x) & c_1) ^ ... ^ (f_nm(x) & c_nm) then you can linComb[x] (is a Block) cast to bool,
            // so linComb using as "bool_vec" (bool function)
            LinearCombination(blockSet, f, coef);

            ai = std::min(AI(f), ai);
        }

        std::ofstream out(
            "netstat_ai_" + std::to_string(Block::SUBBLOCK_SIZE) +
            "_" + std::to_string(Block::NUM_SUBBLOCKS) +
            "_" + std::to_string(Network::ROUNDS) + ".csv",
            std::ios_base::app
        );

        (out ? out : std::cout) << enc.HexKey() << ',' << enc.NetScheme() << ',' << ai << std::endl;
    }

    std::cerr << std::endl;

    return 0;
}
