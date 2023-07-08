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

    for (uint64_t ai, i, min_ai = INT64_MAX,
            nKey = 0; nKey < totalKeys; ++nKey
    ) {
        //aiValues.clear();
        enc.SetRandomTable();
        for (Block coef(1); !coef.IsZero(); ++coef) {
            for (i = 0; i < funcLen; ++i) {
                blockSet[i] = i;
                enc.ProcessBlock(blockSet[i]);
            }
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
