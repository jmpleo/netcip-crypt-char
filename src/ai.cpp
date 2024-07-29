
#include "ai.h"
#include "gaus.h"


int AlgebraicImmunity ( const std::vector<Block> &blockSet )
{
    uint64_t
        i,
        numMonomMaxDegAnnF,
        numMonomMaxDegAnnNegF,
        funcLen = blockSet.size();

    static std::vector<monom_and_deg> monoms(funcLen);
    static bool_mat matrix(funcLen, bool_vec(funcLen >> 1, 0));
    static bool_vec f(funcLen);

    for (i = 0; i < funcLen; ++i) {
        f[i] = static_cast<bool>(blockSet[i]);
    }

    // sorting monoms by deg
    MonomsDeg(monoms);

    // froming matrix, where mat[row][col] = f(a) & monom(a),
    // each col - monom
    // for example, if value of monom is 0x1101 so monom is x1x2x4
    // each row - value of a
    // for example, if value of a is 0x1011 so a is f(1,0,1,1)
    FormingMatrix(matrix, f, monoms);

    // min deg(g) : f & g = 0
    //
    // first dependency column means exist bits a_0,a_1,...,a_col that
    // mat[...][0] & a_0 ^ ... ^ mat[...][col] & a_col = 0
    //
    // or exists monom_1, ..., monom_k that
    // (f & monom_1) ^ ... ^ (f & monom_k) = 0
    //
    // or exist function g = monon_1 ^ ... ^ monom_k that
    // f & g = 0
    //
    // moreover, the monoms are ordered by degrees in the matrix
    // so deg annihilator g is smallest
    numMonomMaxDegAnnF = FirstDependColumn(matrix);

    // the same for ~f - inverse function
    FormingMatrix(matrix, f, monoms, true);
    numMonomMaxDegAnnNegF = FirstDependColumn(matrix);

    return monoms[std::min(numMonomMaxDegAnnF, numMonomMaxDegAnnNegF)].second;
}

int AlgebraicImmunity ( const bool_vec &f )
{
    uint64_t
        numMonomMaxDegAnnF,
        numMonomMaxDegAnnNegF,
        funcLen = f.size();

    static std::vector<monom_and_deg> monoms(funcLen);
    static bool_mat matrix(funcLen, bool_vec(funcLen >> 1, 0));

    // sorting monoms by deg
    MonomsDeg(monoms);

    // froming matrix, where mat[row][col] = f(a) & monom(a),
    //
    // each col - monom
    // for example, if value of monom is 0x1101 so monom is x_1x_2x_4
    //
    // each row - value of a
    // for example, if value of a is 0x1011 so a is f(1,0,1,1)
    FormingMatrix(matrix, f, monoms);

    // min deg(g) : f & g = 0
    //
    // first dependency column means exist bits a_0,a_1,...,a_col that
    // mat[...][0] & a_0 ^ ... ^ mat[...][col] & a_col = 0
    //
    // or exists monom_1, ..., monom_k that
    // (f & monom_1) ^ ... ^ (f & monom_k) = 0
    //
    // or exist function g = monon_1 ^ ... ^ monom_k that
    // f & g = 0
    //
    // moreover, the monoms are ordered by degrees in the matrix
    // so deg annihilator g is smallest
    numMonomMaxDegAnnF = FirstDependColumn(matrix);

    // the same for ~f - inverse function
    FormingMatrix(matrix, f, monoms, true);
    numMonomMaxDegAnnNegF = FirstDependColumn(matrix);

    return monoms[std::min(numMonomMaxDegAnnF, numMonomMaxDegAnnNegF)].second;
}
