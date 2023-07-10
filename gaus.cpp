
#include "gaus.h"
#include "types.h"

#include <algorithm>
#include <bits/stdint-uintn.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>

void FormingMatrix( bool_mat &mat,
                    const bool_vec &func,
                    std::vector<monom_and_deg> &degs,
                    bool negFunc )
{
    uint64_t i, j, monom,
             funcLen = func.size(),
             matCols = funcLen >> 1;
    for (i = 0; i < funcLen; ++i) {
        if (func[i] ^ negFunc) {
            for (j = 0; j < matCols; ++j) {
                monom = degs[j].first;
                mat[i][j]= (
                    ((i | (~monom)) & (funcLen-1)) == (funcLen-1)
                );
            }
        } else {
            std::fill(mat[i].begin(), mat[i].end(), 0);
        }
    }
}
void MonomsDeg( std::vector<monom_and_deg> &deg )
{
    deg[0] = {0, 0};
    deg[1] = {1, 1};
    uint64_t k, i, funcLen = deg.size();
    for (i = 2;
            i < funcLen; i *= 2) {
        for (k = i;
                k < 2*i; k += 2) {
            deg[k] = {k, deg[k - i].second + 1};
            deg[k + 1] = {k + 1, deg[k + 1 - i].second + 1};
        }
    }
    std::stable_sort( deg.begin(),
                      deg.end(),
                      [] (std::pair<uint64_t, int> a, std::pair<int, int> b) {
                        return a.second < b.second;
                      } );
}
uint64_t FirstDependColumn ( bool_mat &mat )
{
    uint64_t i, j, col, row,
             start = 0,
             rowCount = mat.size(),

             // considered half only due to upper estim of AI
             colCount = rowCount >> 1;
    int* index = new int[colCount];

    for (col = 0; col < colCount; ++col) {

        // skip row in column = col where elemets is zero
        for (row = start; row < rowCount && !mat[row][col]; ++row) {}

        // gaus elumination
        if (row < rowCount) {
            if (row != start) {
                std::swap(mat[row], mat[start]);
            }
            for (i = 0, j = col; j < colCount; ++j) {
                if (mat[start][j]) {
                    index[i++] = j;
                }
            }
            for (; i < colCount; ++i) {
                index[i] = -1;
            }
            for (i = start + 1; i < rowCount; ++i) {

                // skip row where element in col position is zero
                if (mat[i][col]) {

                    // skip col where mat[start][j] is zero
                    for (j = 0; index[j] != -1; ++j) {
                        mat[i][index[j]]
                            = mat[i][index[j]] ^ mat[start][index[j]];
                    }
                }
            }
            ++start;
        }
        else {
            // number col of first rows-depend
            colCount = col;
            break;
        }
    }
    delete [] index;
    return colCount;
}

