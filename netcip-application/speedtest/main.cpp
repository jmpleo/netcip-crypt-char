#include "../netcip.h"
#include "../../netcip-research/src/progbar.h"

#include <crypto++/aes.h>
#include <crypto++/des.h>
#include <crypto++/mars.h>
#include <crypto++/chacha.h>
#include <crypto++/threefish.h>
#include <crypto++/3way.h>
#include <crypto++/blowfish.h>
#include <crypto++/cast.h>
#include <crypto++/gost.h>
#include <crypto++/osrng.h>
#include <crypto++/modes.h>
#include <crypto++/filters.h>

#include <chrono>
#include <cstring>
#include <iomanip>
#include <map>
#include <iostream>

#define Now() std::chrono::high_resolution_clock::now()

using namespace CryptoPP;

void randomBytes(byte* bytes, std::size_t nBytes)
{
    AutoSeededRandomPool rng;
    rng.GenerateBlock(bytes, nBytes);
}


int main ()
{
    byte bytesSrc[16];
    byte workBytes[16];
    byte keyBytes[256 * 256];

    std::map<std::string, double> durations;


    int cycle, iter,
        cycles = 10000,
        iterations = 1000;

    ProgressBar<> progbar;

    for (iter = 0; iter < iterations; ++iter) {

        progbar.Show(float(iter) / iterations, std::cerr);

        randomBytes(bytesSrc, sizeof(bytesSrc));
        randomBytes(keyBytes, sizeof(keyBytes));

        { // 16
            AES::Encryption e(keyBytes, AES::DEFAULT_KEYLENGTH);
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) e.ProcessBlock(workBytes);
            auto end = Now();
            durations[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            DES::Encryption e(keyBytes, DES::DEFAULT_KEYLENGTH);
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) e.ProcessBlock(workBytes);
            auto end = Now();
            durations[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            Blowfish::Encryption e(keyBytes, Blowfish::DEFAULT_KEYLENGTH);
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) e.ProcessBlock(workBytes);
            auto end = Now();
            durations[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            CAST128::Encryption e(keyBytes, CAST128::DEFAULT_KEYLENGTH);
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) e.ProcessBlock(workBytes);
            auto end = Now();
            durations[e.AlgorithmName()] += (end - start).count();
        }

        { // 16
            CAST256::Encryption e(keyBytes, CAST256::DEFAULT_KEYLENGTH);
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) e.ProcessBlock(workBytes);
            auto end = Now();
            durations[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            DES_EDE3::Encryption e(keyBytes, DES_EDE3::DEFAULT_KEYLENGTH);
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) e.ProcessBlock(workBytes);
            auto end = Now();
            durations[e.AlgorithmName()] += (end - start).count();
        }

        { // 32
            Threefish256::Encryption e(keyBytes, Threefish256::DEFAULT_KEYLENGTH);
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) e.ProcessBlock(workBytes);
            auto end = Now();
            durations[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            GOST::Encryption e(keyBytes, GOST::DEFAULT_KEYLENGTH);
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) e.ProcessBlock(workBytes);
            auto end = Now();
            durations[e.AlgorithmName()] += (end - start).count();
        }

        { // 16
            MARS::Encryption e(keyBytes, MARS::DEFAULT_KEYLENGTH);
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) e.ProcessBlock(workBytes);
            auto end = Now();
            durations[e.AlgorithmName()] += (end - start).count();
        }

       { // 8
            byte ekey[1<<8][1<<8];
            std::memcpy(ekey, keyBytes, sizeof(ekey));
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) encrypt1_8x8(workBytes, ekey);
            auto end = Now();
            durations["encrypt1_8x8"] += (end - start).count();
        }

        { // 8
            byte ekey[1<<8][1<<8];
            std::memcpy(ekey, keyBytes, sizeof(ekey));
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) encrypt2_8x8(workBytes, ekey);
            auto end = Now();
            durations["encrypt2_8x8"] += (end - start).count();
        }

        { // 16
            byte ekey[1<<8][1<<8];
            std::memcpy(ekey, keyBytes, sizeof(ekey));
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) encrypt1_8x16(workBytes, ekey);
            auto end = Now();
            durations["encrypt1_8x16"] += (end - start).count();
        }

        { // 16
            byte ekey[1<<8][1<<8];
            std::memcpy(ekey, keyBytes, sizeof(ekey));
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));
            auto start = Now();
            for (cycle = 0; cycle < cycles; ++cycle) encrypt2_8x16(workBytes, ekey);
            auto end = Now();
            durations["encrypt2_8x16"] += (end - start).count();
        }
    }

    std::cout << std::endl;

    for (const auto& [cipher, duration] : durations) {
        double blocksPerMinute = (60.0 * 1e6) / duration;
        std::cout
            << std::right << std::setw(30) << cipher << ": "
            << std::left << std::setw(15) << blocksPerMinute << " blocks/minute"
            << std::endl;
    }

    return 0;
}
