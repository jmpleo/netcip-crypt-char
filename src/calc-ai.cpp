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
    NetCip::Enc enc;

    char progressBar[101] = { 0 };
    float progress;

    uint64_t
        ai,
        x,
        minAI,
        nKey,
        funcLen = (1ULL << (enc.SUBBLOCKSIZE * enc.NUMSUBBLOCKS)),
        totalKeys = std::stoull(argv[1]);

    //std::vector<uint64_t> aiValues(funcLen);
    std::vector<Block>
        blockSet(funcLen),
        linComb(funcLen);

    for (nKey = 0; nKey < totalKeys; ++nKey) {
        //aiValues.clear();
        minAI = INT64_MAX;
        enc.SetRandomTable();
        for (Block coef(1); !coef.IsZero(); ++coef) {

            // blockSet[...] is set of value coordinate functions of Enc()
            // where blockSet[x] = (f_1(x), f_2(x), ...,f_nm(x))
            // moreover, x=x_1x_2..x_nm ordered by lexicographic
            for (x = 0; x < funcLen; ++x) {
                blockSet[x] = x;
                enc.ProcessBlock(blockSet[x]);
            }

            // for each x=x_1x_2...x_nm and coef=c_1c_2...c_nm
            // linComb[x] = (f_1(x) & c_1) ^ ... ^ (f_nm(x) & c_nm) then you can linComb[x] (is a Block) cast to bool,
            // so linComb using as "bool_vec" (bool function)
            LinearCombination(blockSet, linComb, coef);
            if (ai = AlgebraicImmunity(linComb), ai < minAI) {
               minAI = ai;
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

        (f ? f : std::cout) << minAI << std::endl;

        progbar.Show(static_cast<float>(nKey) / totalKeys, std::cerr);

        //std::cout << "\rAI: " <<  minAI << " progress: " << nKey + 1 << "/" << totalKeys;
        //std::cout.flush();
    }

    std::cerr << std::endl;

    return 0;
}
