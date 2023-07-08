#include "block.h"
#include "netcip.h"
#include "nl.h"
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
        std::cout << "netstat-nl {volume}\n";
        return 1;
    }

    NetCip::Enc enc;

    uint64_t funcLen = (1ULL << (enc.SUBBLOCKSIZE * enc.NUMSUBBLOCKS));

    uint64_t totalKeys = std::stoull(argv[1]);

    //std::vector<uint64_t> nlValues(funcLen);
    std::vector<Block> blockSet(funcLen),
                       linComb(funcLen);

    for (uint64_t nl, i, min_nl,
            nKey = 0; nKey < totalKeys; ++nKey
    ) {
        //nlValues.clear();
        min_nl = INT64_MAX;
        enc.SetRandomTable();
        for (Block coef(1); !coef.IsZero(); ++coef) {
            for (i = 0; i < funcLen; ++i) {
                blockSet[i] = i;
                enc.ProcessBlock(blockSet[i]);
            }
            LinearCombination(blockSet, linComb, coef);
            nl = NL(linComb);
            if (nl < min_nl) {
              min_nl = nl;
            }
            //nlValues.push_back(nl);
        }

        std::ofstream f(
            "netstat_nl_" + std::to_string(enc.SUBBLOCKSIZE) +
            "_" + std::to_string(enc.NUMSUBBLOCKS) +
            "_" + std::to_string(enc.ROUNDS) + ".csv",
            std::ios_base::app
        );

        //f << *std::min_element(nlValues.begin(), nlValues.end()) << std::endl;
        f << min_nl << std::endl;

        std::cout << "\rprogress: " << nKey << "/" << totalKeys;
        std::cout.flush();
    }
    return 0;
}
