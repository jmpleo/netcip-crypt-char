#include "block.h"
#include "netcip.h"

#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "netstat-mdp {volume}\n";
        return 1;
    }

    NetCip::Enc enc;

    // MDP
    uint64_t totalKeys = std::stoull(argv[1]);
    //std::vector<uint64_t> MDPs(totalKeys);
    for (uint64_t MDP, count,
            nKey = 0; nKey < totalKeys; ++nKey
    ) {
        enc.SetRandomTable();
        MDP = 0;
        for (Block a(1), b, x, dx, df; !a.IsZero(); ++a) {
            for (b = 1; !b.IsZero(); ++b) {
                count = 0;
                x = 0;
                do {
                    dx = x; df = x; dx ^= a;
                    enc.ProcessBlock(dx);  // after: dx = E(x+a)
                    enc.ProcessBlock(df);  // after: df = E(x)
                    if ((df ^= dx) == b) { // E(x+a) + E(x) == b
                        ++count;
                    }
                    ++x;
                } while (!x.IsZero());
                if (count > MDP) {
                    MDP = count;
                }
            }
        }
        //MDPs[nKey] = MDP;

        std::ofstream f(
            "netstat_mdp_" + std::to_string(enc.SUBBLOCKSIZE) +
                       "_" + std::to_string(enc.NUMSUBBLOCKS) +
                       "_" + std::to_string(enc.ROUNDS) + ".csv",
            std::ios_base::app
        );
        f << MDP << std::endl;

        std::cout << "\rprogress: " << nKey << "/" << totalKeys;
        std::cout.flush();
    }

        return 0;
}
