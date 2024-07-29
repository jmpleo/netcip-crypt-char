#include "wa-coef.h"
#include "block.h"
#include "types.h"
#include <cstdint>
#include <vector>


// discrete Fourier transform
void FFT ( int64_t* vec, uint64_t len )
{
    if (len /= 2) {
        for (uint64_t i = 0; i < len; ++i) {
            vec[i] += vec[len + i]; // a + b || b
            vec[len + i] *= -2;     // a + b || -2b
            vec[len + i] += vec[i]; // a + b || a - b
        }
        FFT(vec, len);
        FFT(vec + len, len);
    }
}


/*
 * Walsh spectrum for expand functions (-1^f)
 * of Coeficients of Walsh-Hadamard the 2nd kind
 *
 * -1^f(x) = 2^(-k) * sum_a[ W(a) * -1^<a,x>  ]
 */
std::vector<int64_t> WACoef ( const bool_vec &func )
{
    std::vector<int64_t> coef(func.size());
    for (uint64_t i = 0, n = coef.size(); i < n; ++i) {
        coef[i] = func[i] ? -1 : 1;
    }
    FFT(coef.data(), coef.size());
    return coef;
}

std::vector<int64_t> WACoef ( const std::vector<Block> &blockSetAsBoolFunc )
{
    std::vector<int64_t> coef(blockSetAsBoolFunc.size());
    for (uint64_t i = 0, n = coef.size(); i < n; ++i) {
        coef[i] = static_cast<bool>(blockSetAsBoolFunc[i]) ? -1 : 1;
    }
    FFT(coef.data(), coef.size());
    return coef;
}


