#include "block.h"
#include "net.h"
#include "netcip.h"
#include "nl.h"
#include "lin-comb.h"
#include "progbar.h"

#include <cstdint>

#include <fstream>
#include <ios>
#include <iostream>

#include <string>
#include <vector>

#include <cmath>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "netstat-nl KEYS\n";
        return 1;
    }

    ProgressBar<> progbar;
    Enc enc;

    uint64_t
        nl,
        x,
        minNL,
        nKey,
        funcLen = (1ULL << (Block::SUBBLOCKSIZE * Block::NUMSUBBLOCKS)),
        totalKeys = std::stoull(argv[1]);

    //std::vector<uint64_t> nlValues(funcLen);
    std::vector<Block>
        blockSet(funcLen),
        linComb(funcLen);

    for (nKey = 0; nKey < totalKeys; ++nKey) {
        //nlValues.clear();
        minNL = INT64_MAX;
        enc.UpdateKey();
        for (Block coef(1); !coef.IsZero(); ++coef) {
            for (x = 0; x < funcLen; ++x) {
                blockSet[x] = x;
                enc.ProcessBlock(blockSet[x]);
            }
            LinearCombination(blockSet, linComb, coef);
            if (nl = NL(linComb), nl < minNL) {
              minNL = nl;
            }
            //nlValues.push_back(nl);
        }

        std::ofstream f(
            "netstat_nl_" + std::to_string(Block::SUBBLOCKSIZE) +
                      "_" + std::to_string(Block::NUMSUBBLOCKS) +
                      "_" + std::to_string(Network::ROUNDS) + ".csv",
            std::ios_base::app
        );

        //f << *std::min_element(nlValues.begin(), nlValues.end()) << std::endl;
        (f ? f : std::cout) << enc.HexKey() << ',' << enc.HexNet() << ',' << minNL << std::endl;

        progbar.Show(static_cast<float>(nKey) / totalKeys, std::cerr);

    }

    std::cerr << std::endl;

    return 0;
}
