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

    uint64_t
        MDP,
        xCount,
        nKey,
        totalKeys = std::stoull(argv[1]);

    //std::vector<uint64_t> MDPs(totalKeys);
    for (nKey = 0; nKey < totalKeys; ++nKey) {
        enc.UpdateKey();
        MDP = 0;
        for (Block a(1), b, x, dx, df; !a.IsZero(); ++a) {
            for (b = 1; !b.IsZero(); ++b) {
                xCount = 0;
                x = 0;
                do {
                    dx = x; df = x; dx ^= a;
                    enc.ProcessBlock(dx);  // after: dx = E(x+a)
                    enc.ProcessBlock(df);  // after: df = E(x)
                    df ^= dx;
                    if (df == b) { // E(x+a) + E(x) == b
                        ++xCount;
                    }
                    ++x;
                } while (!x.IsZero());
                if (xCount > MDP) {
                    MDP = xCount;
                }
            }
        }
        //MDPs[nKey] = MDP;

        std::ofstream f(
            "netstat_mdp_" + std::to_string(Block::SUBBLOCKSIZE) +
                       "_" + std::to_string(Block::NUMSUBBLOCKS) +
                       "_" + std::to_string(Network::ROUNDS) + ".csv",
            std::ios_base::app
        );

        (f ? f : std::cout) << enc.HexKey() << ',' << enc.HexNet() << ',' << MDP << std::endl;

        progbar.Show(static_cast<float>(nKey) / totalKeys, std::cerr);

    }

    std::cerr << std::endl;

    return 0;
}
