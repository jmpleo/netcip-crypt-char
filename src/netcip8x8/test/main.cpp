#include "../netcip.h"
#include <cassert>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>



int main()
{
    byte ekey[1<<8][1<<8];
    byte dkey[1<<8][1<<8];

    std::ifstream in;

    for (int i = 0; i < 100; ++i) {

        in.open("cases/key/" + std::to_string(i), std::ios::binary);
        in.read((char*)ekey, sizeof(ekey))
          .read((char*)dkey, sizeof(dkey));
        in.close();

        char block[8];
        char expected[8];
        char test[8];

        in.open("cases/block/" + std::to_string(i), std::ios::binary);
        in.read(test, 8);
        in.close();

        in.open("cases/encrypt1/" + std::to_string(i), std::ios::binary);
        in.read(expected, 8);
        in.close();

        std::memcpy(block, test, 8);

        encrypt1((byte*)block, ekey);

        assert(std::memcmp(block, expected, 8) == 0);

        decipher1((byte*)block, dkey);

        assert(std::memcmp(block, test, 8) == 0);

        std::memcpy(block, test, 8);

        encrypt2((byte*)block, ekey);

        in.open("cases/encrypt2/" + std::to_string(i), std::ios::binary);
        in.read(expected, 8);
        in.close();

        encrypt2((byte*)block, ekey);

        assert(std::memcmp(block, expected, 8) == 0);

        decipher2((byte*)block, dkey);

        assert(std::memcmp(block, test, 8) == 0);

    }

    std::cout << "tests passed\n";

    return 0;
}

