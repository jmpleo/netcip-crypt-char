#include "block.h"
#include "netcip.h"
#include "nl.h"
#include "lin-comb.h"

#include <algorithm>
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

    int funcLen = (1 << (enc.SUBBLOCKSIZE * enc.NUMSUBBLOCKS));

    int tkeys = std::atoi(argv[1]);

    std::vector<uint64_t> nlValues;
    std::vector<Block> blockSet(funcLen),
                       linComb(funcLen);
    for (int nl, i,
             count,
             nkeys = 0; nkeys < tkeys; ++nkeys) {
        enc.SetRandomTable();

        for (Block coef(1); !coef.IsZero(); ++coef) {
            for (i = 0; i < funcLen; ++i) {
                blockSet[i] = i;
                enc.ProcessBlock(blockSet[i]);
            }
            LinearCombination(blockSet, linComb, coef);
            nlValues.push_back(nl = NL(linComb));
        }

        std::ofstream f(
            "netstat_nl_" + std::to_string(enc.SUBBLOCKSIZE) +
            "_" + std::to_string(enc.NUMSUBBLOCKS) +
            "_" + std::to_string(enc.ROUNDS) + ".csv",
            std::ios_base::app
        );

        f << *std::min_element(nlValues.begin(), nlValues.end()) << std::endl;

        std::cout << "\rprogress: " << nkeys << "/" << tkeys;
        std::cout.flush();
    }
    return 0;
}
