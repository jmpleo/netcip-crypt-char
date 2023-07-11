#ifndef GAUS_H
#define GAUS_H

#include "types.h"
#include "block.h"

uint64_t FirstDependColumn ( bool_mat &mat );

void MonomsDeg ( std::vector<monom_and_deg> &deg );

void FormingMatrix ( bool_mat &mat,
                     const bool_vec &func,
                     std::vector<monom_and_deg> &deg,
                     bool negFunc=false );

#endif
