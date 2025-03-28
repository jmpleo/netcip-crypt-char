#include <cstdint>
#include <random>

using byte = std::uint8_t;

inline bool isLeftHalf (int n) { return (((n) & 1) ^ 1); }

inline void setup_keys_4(std::uint64_t const seeds[16], byte ekey[16][8], byte dkey[16][8])
{
    byte bi, bk, pi;

    for (int k, i, j = 0; j < 16; ++j) {

        for (i = 0; i < 8; ++i) {
            ekey[j][i] = ((2*i) << 4) ^ ((2*i) + 1);
        }

        /*
        std::mt19937_64 gen(seeds[j]);

        for (i = 16 - 1; i >= 1; --i) {

            k = std::uniform_int_distribution<int>(0, i)(gen);

            bi = 0b1111 & (ekey[j][i / 2] >> (4 * isLeftHalf(i)));
            bk = 0b1111 & (ekey[j][k / 2] >> (4 * isLeftHalf(k)));

            ekey[j][i / 2] &= (0b1111 << (4 * !isLeftHalf(i)));
            ekey[j][i / 2] ^= (bk << (4 * isLeftHalf(i)));

            ekey[j][k / 2] &= (0b1111 << (4 * !isLeftHalf(k)));
            ekey[j][k / 2] ^= (bi << (4 * isLeftHalf(k)));
        }
        */

        for (i = 0; i < 16; i+=2) {

            bi = ekey[j][i / 2];

            dkey[j][(bi >> 4) & 0b1111] = i;
            dkey[j][(bi     ) & 0b1111] = i + 1;
        }
    }
}



inline void setup_keys_8(std::uint64_t const seeds[256], byte ekey[256][256], byte dkey[256][256])
{
    for (int i, j = 0; j < 256; ++j) {

        for (i = 0; i < 256; ++i) {
            dkey[j][i] = ekey[j][i] = i;
        }

        std::mt19937_64 gen(seeds[j]);

        for (i = 256 - 1; i >= 1; --i) {
            std::swap(
                ekey[j][i],
                ekey[j][std::uniform_int_distribution<int>(0, i)(gen)]
            );
        }

        for (i = 0; i < 256; ++i) {
            dkey[j][ekey[j][i]] = i;
        }
    }
}


