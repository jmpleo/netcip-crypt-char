#include "../netcip.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <iomanip> // Для std::hex и std::setw


std::ostream& hexDump(std::ostream &out, const char* data, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        out << std::hex << std::setw(2) << std::setfill('0')
            << (static_cast <int> (data[i]) & 0xFF)
            ;
    }
    return out;
}


template <unsigned blockSize>
bool testCase(
    char test[blockSize], char expected[blockSize],
    byte ekey[1<<8][1<<8], byte dkey[1<<8][1<<8],
    std::function<void(byte*, byte[1<<8][1<<8])> encrypt,
    std::function<void(byte*, byte[1<<8][1<<8])> decipher,
    int testNumber // Добавляем номер теста
)
{
    char block[blockSize];
    std::copy_n(test, blockSize, block);

    std::cerr << "\nTEST [" << std::setw(3) << testNumber << "]: ";

    encrypt(reinterpret_cast<byte*>(block), ekey);
    if (std::memcmp(block, expected, blockSize) != 0) {
        std::cerr << "\tencrypt FAILED";
        return false;
    }

    std::cerr << "\tencrypt pass";

    decipher(reinterpret_cast<byte*>(block), dkey);
    if (std::memcmp(block, test, blockSize) != 0) {
        std::cerr << ",\tdecipher FAILED";
        return false;
    }

    std::cerr << ",\tdecipher pass";

    return true;
}

int main() {
    byte ekey[1<<8][1<<8];
    byte dkey[1<<8][1<<8];

    char expected[16];
    char test[16];

    std::ifstream in;
    std::string path;
    bool allTestsPassed = true;

    for (int i = 0; i < 100; ++i) {
        // Load keys
        path = std::string(TEST_DIR).append("/cases/key/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read((char*)ekey, sizeof(ekey))
          .read((char*)dkey, sizeof(dkey));
        in.close();

        // Test 8x8 encryption and decryption
        path = std::string(TEST_DIR).append("/cases/block/8/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(test, 8);
        in.close();

        path = std::string(TEST_DIR).append("/cases/encrypt1/8/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(expected, 8);
        in.close();

        allTestsPassed = allTestsPassed && testCase<8>(
            test, expected,
            ekey, dkey,
            &encrypt1_8x8, &decipher1_8x8,
            i
        );

        path = std::string(TEST_DIR).append("/cases/encrypt2/8/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(expected, 8);
        in.close();

        allTestsPassed = allTestsPassed && testCase<8>(
            test, expected,
            ekey, dkey,
            &encrypt2_8x8, &decipher2_8x8,
            i
        );

        // Test 8x16 encryption and decryption
        path = std::string(TEST_DIR).append("/cases/block/16/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(test, 16);
        in.close();

        path = std::string(TEST_DIR).append("/cases/encrypt1/16/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(expected, 16);
        in.close();

        allTestsPassed = allTestsPassed && testCase<16>(
            test, expected,
            ekey, dkey,
            &encrypt2_8x16, &decipher1_8x16,
            i
        );

        path = std::string(TEST_DIR).append("/cases/encrypt2/16/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(expected, 16);
        in.close();

        allTestsPassed = allTestsPassed && testCase<16>(
            test, expected,
            ekey, dkey,
            &encrypt2_8x16, &decipher2_8x16,
            i
        );
    }

    if (not allTestsPassed) {
        std::cerr << "\nSome tests failed\n";
        return 1;
    }

    std::cout << "\nAll tests passed\n";
    return 0;
}
