#pragma once

#include "types.h"
#include <vector>

std::uint64_t FirstDependentColumn ( std::vector<std::vector<bool>> & mat );

void InitMonomsWithDegree ( std::vector<std::pair<std::uint64_t, unsigned>> & deg );

void InitMatrix (
    std::vector<std::vector<bool>> & mat,
    std::vector<bool> const & f,
    std::vector<std::pair<std::uint64_t, unsigned>> const & deg,
    bool notf = false
);

