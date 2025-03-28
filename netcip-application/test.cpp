#include "key.h"
#include <iomanip>
#include <ios>
#include <iostream>



int main()
{
    byte ekey[16][8];
    byte dkey[16][8];

    std::uint64_t seeds[16] = { 0 };

    setup_keys_4(seeds, ekey, dkey);

    std::cout << "ekey:\n";
    for (int i = 0; i < 16; ++i) {
        std::cout << std::setw(1) << std::hex << i << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < 16; ++i) {
        std::cout << std::setw(1) << std::hex << ((ekey[0][i / 2] >> (4 * isLeftHalf(i))) & 0b1111) << " ";
    } std::cout << "\n\n";

    std::cout << "dkey:\n";
    for (int i = 0; i < 16; ++i) {
        std::cout << std::setw(1) << std::hex << i << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < 16; ++i) {
        std::cout << std::setw(1) << std::hex << ((dkey[0][i / 2] >> (4 * isLeftHalf(i))) & 0b1111) << " ";
    }

    byte ekey8[256][256];
    byte dkey8[256][256];

    std::uint64_t seeds8[256] = { 0 };

    setup_keys_8(seeds8, ekey8, dkey8);
    /*

    std::cout << "8:\n";
    std::cout << "ekey:\n";
    for (int i = 0; i < 256; ++i) {
        std::cout << '(' << std::setw(2) << std::hex << i << ", ";
        std::cout << std::setw(2) << std::hex << int(ekey8[0][i]) << ") ";
        std::cout << "\n";
    } std::cout << "\n\n";

    std::cout << "dkey:\n";
    for (int i = 0; i < 256; ++i) {
        std::cout << '(' << std::setw(2) << std::hex << i << ", ";
        std::cout << std::setw(2) << std::hex << int(dkey8[0][i]) << ") ";
        std::cout << "\n";
    } std::cout << "\n\n";




    */


}
