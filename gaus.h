#ifndef GAUS_H
#define GAUS_H

#include "types.h"
#include "block.h"

uint64_t FirstDepend  (bool_mat &mat);
void     FormingMatrix(bool_mat &mat, const bool_vec &func,
                   std::vector<std::pair<uint64_t,int>> &deg, bool negFunc=false);
void     MonomsDeg(std::vector<std::pair<uint64_t,int>> &deg);

#endif
