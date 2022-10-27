#include "block.h"
#include "netcip.h"
#include "ai.h"
#include "lin-comb.h"

#include <fstream>
#include <iostream>
#include <vector>

int main()
{

    std::uint64_t i, j, k ,
        funcLen = (1 << 12);

    NetCip::Enc enc;
    NetCip::Dec dec;
    //enc.SetRandomTable();
    enc.LoadTable("key");
    dec.LoadTable("key");

    std::vector<int> aiValues;
    std::vector<Block> blockSet(funcLen),
                       linComb(funcLen);
    for (Block coef(1); !coef.IsZero(); ++coef) {
        for (i = 0; i < funcLen; ++i) {
            blockSet[i] = i;
            enc.ProcessBlock(blockSet[i]);
        }
        LinearCombination(blockSet, linComb, coef);
        aiValues.push_back(k = AlgebraicImmunity(linComb));
        std::cout << k << '\n';
    }

    std::ofstream fp("ai-value.txt");
    if (fp.is_open()) {
        for (i = 0, k = aiValues.size(); i < k; ++i)
            fp << aiValues[i] << '\n';
    }
    return 0;
/*
    block.Print();
    enc.ProcessBlock(block);
    block.Print();
    dec.ProcessBlock(block);
    block.Print();
*/}
