#include "block.h"
#include "netcip.h"

#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

#include <numeric>

double Average(std::vector<int> v) {
    return std::accumulate(v.begin(), v.end(), 0.) / static_cast<double>(v.size());
}

double Variance(std::vector<int> v, double average) {
    return std::accumulate(v.begin(), v.end(), 0.,
                           [](double acc, int next) {
                                return (acc + (static_cast<double>(next)
                                             * static_cast<double>(next)));
                           }) / static_cast<double>(v.size())
                              - (average * average);
}

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
    for (int MDP, count, nkeys = 0; nkeys < tkeys; ++nkeys) {
        enc.SetRandomTable();
        MDP = 0;
        for (Block a(1), b, x, dx, df; !a.IsZero(); ++a) {
            for (b = 1; !b.IsZero(); ++b) {
                count = 0;
                x = 0;
                do {                    dx = x;
                    df = x;
                    dx ^= a;
                    enc.ProcessBlock(dx); // after: dx = f(x+a)
                    enc.ProcessBlock(df); // after: df = f(x)
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
    }

    std::ofstream f("netstat-mdp.csv", std::ios_base::app);

    f << enc.SUBBLOCKSIZE << ','
      << enc.NUMSUBBLOCKS << ','
      << enc.ROUNDS << ','
      << MDPs.size()<< ','
      << Average(MDPs)<< ','
      << Variance(MDPs, Average(MDPs))
      << std::endl;

    return 0;
}
