#ifndef LINCOMB_H
#define LINCOMB_H

#include "block.h"

#include <memory.h>

void LinearCombination( std::vector<Block> &source,
                        std::vector<Block> &dest,
                        Block & coef );

#endif
