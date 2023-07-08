#include "wa-coef.h"
#include "block.h"
#include "types.h"
#include <type_traits>
#include <utility>
#include <vector>


void FFT(int64_t* vec, uint64_t len)
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

void WACoef(const std::vector<Block> &blockSetAsBoolFunc)
{
  std::vector<int64_t> func(blockSetAsBoolFunc.size());
  for (uint64_t i = 0, n = func.size(); i < n; ++i) {
    func[i] = static_cast<bool>(blockSetAsBoolFunc[i]) ? -1 : 1;
  }
  FFT(func.data(), func.size());
}


