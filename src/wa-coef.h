#pragma once

#include "types.h"
#include "block.h"

#include <cstdint>
#include <vector>

std::vector<int64_t> WACoef ( const bool_vec &func );

std::vector<int64_t> WACoef ( const std::vector<Block> &blockSet );

