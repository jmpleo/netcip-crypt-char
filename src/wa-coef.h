#ifndef WA_COEF_H
#define WA_COEF_H

#include "types.h"
#include "block.h"

#include <cstdint>
#include <vector>

std::vector<int64_t> WACoef ( const bool_vec &func );

std::vector<int64_t> WACoef ( const std::vector<Block> &blockSet );

#endif

