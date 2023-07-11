#ifndef NL_H
#define NL_H

#include "types.h"
#include "wa-coef.h"

#include <cmath>
#include <cstdint>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <iostream>

inline uint64_t NL ( const bool_vec &func );
inline uint64_t NL ( const std::vector<Block> &blockSetAsBoolFunc );

inline uint64_t NL ( const bool_vec &func )
{
    auto coef = WACoef(func);

    // for bool func f (with 2^k variables) NL is 2^(k-1) - max|W(a)|,
    // where W(a) - Walsh spectrum for expand functions (-1^f)
    // of Coeficients of Walsh-Hadamard the 2nd kind
    return (coef.size() >> 1) - (
        std::abs(
            *std::max_element(
                coef.begin(), coef.end(),
                [] (int64_t a, int64_t b) {
                    return std::abs(a) < std::abs(b);
                }
            )
        ) >> 1
    );
}

inline uint64_t NL(const std::vector<Block> &blockSetAsBoolFunc)
{
    auto coef = WACoef(blockSetAsBoolFunc);
    return (coef.size() >> 1) - (
        std::abs(
            *std::max_element(
                coef.begin(), coef.end(),
                [] (int64_t a, int64_t b) {
                    return std::abs(a) < std::abs(b);
                }
            )
        ) >> 1
    );
}

#endif
