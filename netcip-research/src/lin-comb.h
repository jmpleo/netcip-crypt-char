#pragma once

#include "block.h"

void LinearCombination( std::vector<Block> const & funcSet,
                        std::vector<bool> & linearComb,
                        Block & coef );

