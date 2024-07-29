#pragma once

#include "types.h"

uint64_t FirstDependColumn ( bool_mat &mat );

void MonomsDeg ( std::vector<monom_and_deg> &deg );

void FormingMatrix ( bool_mat &mat,
                     const bool_vec &func,
                     std::vector<monom_and_deg> &deg,
                     bool negFunc=false );

