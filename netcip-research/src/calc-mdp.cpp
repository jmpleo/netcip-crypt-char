#include "block.h"
#include "net.h"
#include "netcip.h"
#include "progbar.h"

#include <cstdint>

#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>

#include <string>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "netstat-mdp KEYS\n";
        return 1;
    }

    ProgressBar<> progbar;
    Enc enc;

    std::uint64_t
        mdp,
        xCount,
        nKey,
        totalKeys = std::stoull(argv[1]);

    //std::vector<uint64_t> MDPs(totalKeys);
    for (nKey = 0; nKey < totalKeys; ++nKey) {

        progbar.Show(static_cast<float>(nKey) / totalKeys, std::cerr);

        enc.UpdateKey();
        mdp = 0;

        for (Block b, x, dx, df, a{1}; !a.IsZero(); ++a) {
            for (b = 1; !b.IsZero(); ++b) {
                xCount = 0;
                x = 0;
                do {
                    dx = x; df = x; dx ^= a;

                    enc(dx);  // after: dx = E(x+a)
                    enc(df);  // after: df = E(x)

                    df ^= dx;

                    // E(x+a) + E(x) == b
                    if (df == b) { ++xCount; }

                    ++x;

                } while (!x.IsZero());

                mdp = std::min(mdp, xCount);
            }
        }

        std::ofstream out(
            "netstat_mdp_" + std::to_string(Block::SUBBLOCK_SIZE) +
                       "_" + std::to_string(Block::NUM_SUBBLOCKS) +
                       "_" + std::to_string(Network::ROUNDS) + ".csv",
            std::ios_base::app
        );

        (out ? out : std::cout) << enc.HexKey() << ',' << enc.NetScheme() << ',' << mdp << std::endl;

    }

    std::cerr << std::endl;

    return 0;
}
