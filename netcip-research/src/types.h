#pragma once

#include <cstdint>
#include <vector>

using bool_vec = std::vector<bool>;
using bool_mat = std::vector<bool_vec>;
using byte = std::uint8_t;
using monom_t = std::uint64_t;
using monom_and_deg = std::pair<monom_t, unsigned>;
