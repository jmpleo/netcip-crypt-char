#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <vector>

typedef std::vector<bool>
        bool_vec;
typedef std::vector<bool_vec>
        bool_mat;
typedef std::uint8_t
        byte;
typedef uint16_t
        monom_t;
typedef std::pair<monom_t, int>
        monom_and_deg;
#endif
