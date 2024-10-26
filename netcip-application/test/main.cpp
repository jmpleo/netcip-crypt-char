#include "../netcip.h"
#include <cassert>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>


void test1_8x8(char test[8], char expected[8], byte ekey[1<<8][1<<8], byte dkey[1<<8][1<<8])
{
    char block[8];
    std::memcpy(block, test, 8);

    encrypt1_8x8((byte*)block, ekey);
    assert(std::memcmp(block, expected, 8) == 0);

    decipher1_8x8((byte*)block, dkey);
    assert(std::memcmp(block, test, 8) == 0);
}

void test2_8x8(char test[8], char expected[8], byte ekey[1<<8][1<<8], byte dkey[1<<8][1<<8])
{
    char block[8];
    std::memcpy(block, test, 8);

    encrypt2_8x8((byte*)block, ekey);
    assert(std::memcmp(block, expected, 8) == 0);

    decipher2_8x8((byte*)block, dkey);
    assert(std::memcmp(block, test, 8) == 0);
}


void test1_8x16(char test[16], char expected[16], byte ekey[1<<8][1<<8], byte dkey[1<<8][1<<8])
{
    char block[16];
    std::memcpy(block, test, 16);

    encrypt1_8x16((byte*)block, ekey);
    assert(std::memcmp(block, expected, 16) == 0);

    decipher1_8x16((byte*)block, dkey);
    assert(std::memcmp(block, test, 16) == 0);
}

void test2_8x16(char test[16], char expected[16], byte ekey[1<<8][1<<8], byte dkey[1<<8][1<<8])
{
    char block[16];
    std::memcpy(block, test, 16);

    encrypt2_8x16((byte*)block, ekey);
    assert(std::memcmp(block, expected, 16) == 0);

    decipher2_8x16((byte*)block, dkey);
    assert(std::memcmp(block, test, 16) == 0);
}


int main()
{
    byte ekey[1<<8][1<<8];
    byte dkey[1<<8][1<<8];

    char expected[16];
    char test[16];

    std::ifstream in;
    std::string path;

    for (int i = 0; i < 100; ++i) {

        path = std::string(TEST_DIR).append("/cases/key/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read((char*)ekey, sizeof(ekey))
          .read((char*)dkey, sizeof(dkey));
        in.close();

        path = std::string(TEST_DIR).append("/cases/block/8/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(test, 8);
        in.close();

        path = std::string(TEST_DIR).append("/cases/encrypt1/8/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(expected, 8);
        in.close();

        test1_8x8(test, expected, ekey, dkey);

        path = std::string(TEST_DIR).append("/cases/encrypt2/8/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(expected, 8);
        in.close();

        test2_8x8(test, expected, ekey, dkey);

        path = std::string(TEST_DIR).append("/cases/block/16/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(test, 16);
        in.close();

        path = std::string(TEST_DIR).append("/cases/encrypt1/16/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(expected, 16);
        in.close();

        test1_8x16(test, expected, ekey, dkey);

        path = std::string(TEST_DIR).append("/cases/encrypt2/16/").append(std::to_string(i));
        in.open(path, std::ios::binary);
        in.read(expected, 16);
        in.close();

        test2_8x16(test, expected, ekey, dkey);
    }

    std::cout << "tests passed\n";

    return 0;
}

