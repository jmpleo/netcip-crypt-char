#include "block.h"
#include "netcip.h"
#include "ai.h"
#include "lin-comb.h"

#include <algorithm>
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

    int funcLen = (1 << (enc.SUBBLOCKSIZE * enc.NUMSUBBLOCKS));

    int tkeys = std::atoi(argv[1]);

    std::vector<int> aiValues;
    std::vector<Block> blockSet(funcLen),
                       linComb(funcLen);
    for (int ai, i,
             count,
             nkeys = 0; nkeys < tkeys; ++nkeys) {
        enc.SetRandomTable();

        for (Block coef(1); !coef.IsZero(); ++coef) {
            for (i = 0; i < funcLen; ++i) {
                blockSet[i] = i;
                enc.ProcessBlock(blockSet[i]);
            }
            LinearCombination(blockSet, linComb, coef);
            aiValues.push_back(ai = AlgebraicImmunity(linComb));
        }

        std::ofstream f(
            "netstat_ai_" + std::to_string(enc.SUBBLOCKSIZE) +
            "_" + std::to_string(enc.NUMSUBBLOCKS) +
            "_" + std::to_string(enc.ROUNDS) + ".csv",
            std::ios_base::app
        );

        f << *std::min(aiValues.begin(), aiValues.end()) << std::endl;

        std::cout << "\rprogress: " << nkeys << "/" << tkeys;
        std::cout.flush();
    }
    return 0;
}
