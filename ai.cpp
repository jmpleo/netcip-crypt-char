
#include "ai.h"
#include "gaus.h"

int AlgebraicImmunity(const std::vector<Block> &blockSet)
{
    uint64_t i, k, s, funcLen = blockSet.size();
    static std::vector<std::pair<uint64_t, int>> degs(funcLen);
    static bool_mat matrix(funcLen, bool_vec(funcLen >> 1, 0));
    static bool_vec f(funcLen);
    for (i = 0; i < funcLen; ++i) {
        f[i] = static_cast<bool>(blockSet[i]);
    }
    MonomsDeg(degs);
    FormingMatrix(matrix, f, degs);
    k = FirstDepend(matrix);
    FormingMatrix(matrix, f, degs, true);
    s = FirstDepend(matrix);
    return degs[k < s ? k : s].second;
}

int AlgebraicImmunity(const std::vector<bool> &func)
{
    uint64_t i, k, s, funcLen = func.size();
    static std::vector<std::pair<uint64_t, int>> degs(funcLen);
    static bool_mat matrix(funcLen, bool_vec(funcLen >> 1, 0));
    MonomsDeg(degs);
    FormingMatrix(matrix, func, degs);
    k = FirstDepend(matrix);
    FormingMatrix(matrix, func, degs, true);
    s = FirstDepend(matrix);
    return degs[k < s ? k : s].second;
}

