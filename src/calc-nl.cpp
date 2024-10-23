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

    std::uint64_t
        nl,
        x,
        nKey,
        funcLen = (1ULL << Block::BLOCKSIZE),
        totalKeys = std::stoull(argv[1]);

    std::vector<Block> blockSet(funcLen);
    std::vector<bool> f(funcLen);

    for (nKey = 0; nKey < totalKeys; ++nKey) {

        progbar.Show(static_cast<float>(nKey) / totalKeys, std::cerr);

        nl = INT64_MAX;

        enc.UpdateKey();

        for (x = 0; x < funcLen; ++x) {
            blockSet[x] = x;
            enc.ProcessBlock(blockSet[x]);
        }

        for (Block coef{1}; !coef.IsZero(); ++coef) {

            LinearCombination(blockSet, f, coef);

            nl = std::min(NL(f), nl);

        }

        std::ofstream out(
            "netstat_nl_" + std::to_string(Block::SUBBLOCK_SIZE) +
                      "_" + std::to_string(Block::NUM_SUBBLOCKS) +
                      "_" + std::to_string(Network::ROUNDS) + ".csv",
            std::ios_base::app
        );

        //f << *std::min_element(nlValues.begin(), nlValues.end()) << std::endl;
        (out ? out : std::cout) << enc.HexKey() << ',' << enc.NetScheme() << ',' << nl << std::endl;

    }

    std::cerr << std::endl;

    return 0;
}
