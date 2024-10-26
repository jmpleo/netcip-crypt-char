#pragma once

#include "types.h"
#include "wa-coef.h"

#include <cmath>
#include <cstdint>
#include <algorithm>
#include <cstdint>
#include <vector>


inline uint64_t NL ( const std::vector<bool> & func )
{
    auto coef = WACoef(func);

    // for bool func f (with 2^k variables) NL is 2^(k-1) - max|W(a)|,
    // where W(a) - Walsh spectrum for expand functions (-1^f)
    // of Coeficients of Walsh-Hadamard the 2nd kind
    return (coef.size() >> 1) - (
        std::abs(
            *std::max_element(coef.begin(), coef.end(),
                [] (std::int64_t a, std::int64_t b) {
                    return std::abs(a) < std::abs(b);
                }
            )
        ) >> 1
    );
}

