#include "block.h"
#include "netcip.h"
#include "ai.h"
#include "lin-comb.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

#include <numeric>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "netstat-ai {volume}\n";
        return 1;
    }

    NetCip::Enc enc;

    uint64_t funcLen = (1ULL << (enc.SUBBLOCKSIZE * enc.NUMSUBBLOCKS));

    uint64_t totalKeys = std::stoull(argv[1]);

    //std::vector<uint64_t> aiValues(funcLen);
    std::vector<Block> blockSet(funcLen),
                       linComb(funcLen);

    for (uint64_t ai, i, min_ai,
            nKey = 0; nKey < totalKeys; ++nKey
    ) {
        //aiValues.clear();
        min_ai = INT64_MAX;
        enc.SetRandomTable();
        for (Block coef(1); !coef.IsZero(); ++coef) {

            // blockSet[...] is set of value coordinate functions of Enc()
            // where blockSet[x] = (f_1(x), f_2(x), ...,f_nm(x))
            // moreover, x=x_1x_2..x_nm ordered by lexicographic
            for (i = 0; i < funcLen; ++i) {
                blockSet[i] = i;
                enc.ProcessBlock(blockSet[i]);
            }

            // for each x=x_1x_2...x_nm and coef=c_1c_2...c_nm
            // linComb[x] = (f_1(x) & c_1) ^ ... ^ (f_nm(x) & c_nm)
            // then you can linComb[x] (is a Block) cast to bool,
            // so linComb using as "bool_vec" (bool function)
            LinearCombination(blockSet, linComb, coef);
            ai = AlgebraicImmunity(linComb);
            if (ai < min_ai) {
               min_ai = ai;
            }
            //aiValues.push_back(ai);
        }

        std::ofstream f(
            "netstat_ai_" + std::to_string(enc.SUBBLOCKSIZE) +
            "_" + std::to_string(enc.NUMSUBBLOCKS) +
            "_" + std::to_string(enc.ROUNDS) + ".csv",
            std::ios_base::app
        );

        //f << *std::min_element(aiValues.begin(), aiValues.end()) << std::endl;
        f << min_ai << std::endl;

        std::cout << "\rprogress: " << nKey << "/" << totalKeys;
        std::cout.flush();
    }
    return 0;
}
