
#include "gaus.h"
#include "types.h"

#include <algorithm>
#include <bits/stdint-uintn.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <utility>
#include <vector>


void InitMatrix(
    std::vector<std::vector<bool>> & mat,
    std::vector<bool> const & f,
    std::vector<std::pair<std::uint64_t, unsigned>> const & degs,
    bool notf
)
{
    std::uint64_t
        i,
        j,
        funcLen = f.size(),
        matCols = funcLen >> 1;

    for (i = 0; i < funcLen; ++i) {
        if (f[i] ^ notf) {
            for (j = 0; j < matCols; ++j) {
                mat[i][j] = (
                    // monom(i)
                    ((i | ~degs[j].first) & (funcLen - 1)) == (funcLen - 1)
                );
            }
        }
    }
}


void InitMonomsWithDegree(std::vector<std::pair<std::uint64_t, unsigned int>> &deg)
{

    std::uint64_t
        k,
        i,
        funcLen = deg.size();

    deg[0] = {0, 0};
    deg[1] = {1, 1};

    for (i = 2; i < funcLen; i *= 2) {
        for (k = i; k < 2*i; k += 2) {
            deg[k    ] = {k,    deg[k - i].second + 1};
            deg[k + 1] = {k + 1, deg[k + 1 - i].second + 1};
        }
    }

    std::stable_sort(
        deg.begin(),
        deg.end(),
        [] (std::pair<uint64_t, int> a, std::pair<int, int> b) {
            return a.second < b.second;
        }
    );
}


std::uint64_t FirstDependentColumn(std::vector<std::vector<bool>> &mat)
{
    std::uint64_t
        i,
        j,
        col,
        row,
        stop,
        start = 0,
        rowCount = mat.size(),

        // considered half only due to upper estim of AI
        colCount = rowCount >> 1;

    // optimization array with index non zero elem in pivot row
    std::vector<int> index(colCount);

    for (col = 0; col < colCount; ++col) {

        // skip row in column = col where elemets is zero
        for (row = start; row < rowCount && !mat[row][col]; ++row) {}

        // number col of first cols-depend
        if (row >= rowCount) {
            colCount = col;
            break;
        }

        // gaus elumination
        if (row != start) {
            std::swap(mat[row], mat[start]);
        }
        for (i = 0, j = col; j < colCount; ++j) {
            index[i] = j;
            i += (std::uint64_t)(mat[start][j]);
            //if (mat[start][j]) {
            //    index[i] = j;
            //    i++;
            //}
        }
        stop = i;
        //for (; i < colCount; ++i) {
        //    index[i] = -1;
        //}
        for (i = start + 1; i < rowCount; ++i) {

            // skip row where element in col position is zero
            if (mat[i][col]) {

                // skip col where mat[start][j] is zero
                // for (j = 0; index[j] != -1; ++j) {
                for (j = 0; j < stop; ++j) {
                    mat[i][ index[j] ] = mat[i][ index[j] ] ^ mat[start][ index[j] ];
                }
            }
        }

        ++start;
    }

    return colCount;
}

