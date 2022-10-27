
#include "ai.h"
#include "gaus.h"

int AlgebraicImmunity(std::vector<Block> &blockSet)
{
    uint64_t i, k, s, funcLen = blockSet.size();
    static std::vector<std::pair<uint64_t, int>> degs(funcLen);
    static bool_mat matrix(funcLen, bool_vec(funcLen >> 1, 0));
    static bool_vec f(funcLen), cf(funcLen);
    for (i = 0; i < funcLen; ++i) {
        f[i] = !(cf[i] = blockSet[i].IsZero());
    }
    MonomsDeg(degs);
    FormingMatrix(matrix, f, degs);
    k = FirstDepend(matrix);
    FormingMatrix(matrix, cf, degs);
    s = FirstDepend(matrix);
    return degs[k < s ? k : s].second;
}
