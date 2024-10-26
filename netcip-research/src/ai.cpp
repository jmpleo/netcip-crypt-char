
#include "ai.h"
#include "gaus.h"
#include <vector>


unsigned AI ( std::vector<bool> const & f )
{
    std::uint64_t
        numMonomMaxDegAnnF,
        numMonomMaxDegAnnNegF,
        funcLen = f.size();

    static std::vector<std::pair<std::uint64_t, unsigned>>
        monoms(funcLen);
    static std::vector<std::vector<bool>>
        matrix(funcLen, std::vector<bool>(funcLen >> 1, 0));

    // sorting monoms by deg
    InitMonomsWithDegree(monoms);

    // froming matrix, where mat[row][col] = f(a) & monom(a),
    //
    // each col - monom
    // for example, if value of monom is 0x1101 so monom is x_1x_2x_4
    //
    // each row - value of a
    // for example, if value of a is 0x1011 so a is f(1,0,1,1)
    InitMatrix(matrix, f, monoms);

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
    numMonomMaxDegAnnF = FirstDependentColumn(matrix);

    // the same for ~f - inverse function
    InitMatrix(matrix, f, monoms, true);

    numMonomMaxDegAnnNegF = FirstDependentColumn(matrix);

    return monoms[std::min(numMonomMaxDegAnnF, numMonomMaxDegAnnNegF)].second;
}
