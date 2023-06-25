#include "block.h"
#include "netcip.h"

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
    int tkeys = std::atoi(argv[1]);
    std::vector<int> MDPs(tkeys);
    for (int MDP,
            count,
            nkeys = 0; nkeys < tkeys; ++nkeys) {
        enc.SetRandomTable();
        MDP = 0;
        for (Block a(1), b, x, dx, df; !a.IsZero(); ++a) {
            for (b = 1; !b.IsZero(); ++b) {
                count = 0;
                x = 0;
                do {
                    dx = x;
                    df = x;
                    dx ^= a;
                    enc.ProcessBlock(dx); // after: dx = F(x+a)
                    enc.ProcessBlock(df); // after: df = F(x)
                    if ((df ^= dx) == b) {
                        ++count;
                    }
                    ++x;
                } while (!x.IsZero());
                if (count > MDP) {
                    MDP = count;
                }
            }
        }
        MDPs[nkeys] = MDP;

        std::ofstream f(
            "netstat_mdp_" + std::to_string(enc.SUBBLOCKSIZE) +
                       "_" + std::to_string(enc.NUMSUBBLOCKS) +
                       "_" + std::to_string(enc.ROUNDS) + ".csv",
            std::ios_base::app
        );
        f << MDP << std::endl;

        std::cout << "\rprogress: " << nkeys << "/" << tkeys;
        std::cout.flush();
    }

        return 0;
}
