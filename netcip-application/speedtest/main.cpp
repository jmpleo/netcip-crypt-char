#include "../netcip.h"
#include "../../netcip-research/src/progbar.h"

#include <crypto++/aes.h>
#include <crypto++/cryptlib.h>
#include <crypto++/serpent.h>
#include <crypto++/camellia.h>
#include <crypto++/rc2.h>
#include <crypto++/rc5.h>
#include <crypto++/rc6.h>
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

constexpr int CYCLES = 1000;
constexpr int ITERATIONS = 1000;

std::chrono::high_resolution_clock::time_point now() {
    return std::chrono::high_resolution_clock::now();
}

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
    byte keyBytes[256 * 256 * 2];

    std::map<std::string, double> durations8;
    std::map<std::string, double> durations16;
    std::map<std::string, double> durations32;

    std::map<std::string, double> encDurations8;
    std::map<std::string, double> encDurations16;
    std::map<std::string, double> encDurations32;

    std::map<std::string, double> decDurations8;
    std::map<std::string, double> decDurations16;
    std::map<std::string, double> decDurations32;

    int cycle, iter;

    ProgressBar<> progbar;

    decltype(now()) start, end;

    for (iter = 0; iter < ITERATIONS; ++iter) {

        progbar.Show(float(iter) / ITERATIONS, std::cerr);

        randomBytes(bytesSrc, sizeof(bytesSrc));
        randomBytes(keyBytes, sizeof(keyBytes));

#define     ENC_CHECK { std::memcpy(workBytes, bytesSrc, sizeof(workBytes)); \
                start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) { \
                    e.ProcessBlock(workBytes); \
                } end = now(); }

#define     DEC_CHECK { std::memcpy(workBytes, bytesSrc, sizeof(workBytes)); \
                start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) { \
                    d.ProcessBlock(workBytes); \
                } end = now(); }

#define     ENCDEC_CHECK { std::memcpy(workBytes, bytesSrc, sizeof(workBytes)); \
                start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) { \
                    e.ProcessBlock(workBytes); \
                    d.ProcessBlock(workBytes); \
                } end = now(); }

        { // 16
            AES::Encryption e(keyBytes, AES::DEFAULT_KEYLENGTH);
            AES::Decryption d(keyBytes, AES::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations16[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations16[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations16[e.AlgorithmName()] += (end - start).count();

        }

        { // 8
            DES::Encryption e(keyBytes, DES::DEFAULT_KEYLENGTH);
            DES::Decryption d(keyBytes, DES::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations8[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations8[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations8[e.AlgorithmName()] += (end - start).count();
       }

        { // 8
            RC2::Encryption e(keyBytes, RC2::DEFAULT_KEYLENGTH);
            RC2::Decryption d(keyBytes, RC2::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations8[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations8[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations8[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            RC5::Encryption e(keyBytes, RC5::DEFAULT_KEYLENGTH);
            RC5::Decryption d(keyBytes, RC5::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations8[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations8[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations8[e.AlgorithmName()] += (end - start).count();
        }

        { // 16
            Serpent::Encryption e(keyBytes, Serpent::DEFAULT_KEYLENGTH);
            Serpent::Decryption d(keyBytes, Serpent::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations16[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations16[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations16[e.AlgorithmName()] += (end - start).count();
        }

        { // 16
            RC6::Encryption e(keyBytes, RC6::DEFAULT_KEYLENGTH);
            RC6::Decryption d(keyBytes, RC6::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations16[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations16[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations16[e.AlgorithmName()] += (end - start).count();
        }

        { // 16
            Camellia::Encryption e(keyBytes, Camellia::DEFAULT_KEYLENGTH);
            Camellia::Decryption d(keyBytes, Camellia::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations16[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations16[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations16[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            Blowfish::Encryption e(keyBytes, Blowfish::DEFAULT_KEYLENGTH);
            Blowfish::Decryption d(keyBytes, Blowfish::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations8[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations8[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations8[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            CAST128::Encryption e(keyBytes, CAST128::DEFAULT_KEYLENGTH);
            CAST128::Decryption d(keyBytes, CAST128::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations8[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations8[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations8[e.AlgorithmName()] += (end - start).count();
        }

        { // 16
            CAST256::Encryption e(keyBytes, CAST256::DEFAULT_KEYLENGTH);
            CAST256::Decryption d(keyBytes, CAST256::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations16[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations16[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations16[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            DES_EDE3::Encryption e(keyBytes, DES_EDE3::DEFAULT_KEYLENGTH);
            DES_EDE3::Decryption d(keyBytes, DES_EDE3::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations8[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations8[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations8[e.AlgorithmName()] += (end - start).count();
        }

        { // 32
            Threefish256::Encryption e(keyBytes, Threefish256::DEFAULT_KEYLENGTH);
            Threefish256::Decryption d(keyBytes, Threefish256::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations32[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations32[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations32[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            GOST::Encryption e(keyBytes, GOST::DEFAULT_KEYLENGTH);
            GOST::Decryption d(keyBytes, GOST::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations8[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations8[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations8[e.AlgorithmName()] += (end - start).count();
        }

        { // 16
            MARS::Encryption e(keyBytes, MARS::DEFAULT_KEYLENGTH);
            MARS::Decryption d(keyBytes, MARS::DEFAULT_KEYLENGTH);

            ENCDEC_CHECK durations16[e.AlgorithmName()] += (end - start).count();
            ENC_CHECK encDurations16[e.AlgorithmName()] += (end - start).count();
            DEC_CHECK decDurations16[e.AlgorithmName()] += (end - start).count();
        }

        { // 8
            byte ekey[1<<8][1<<8];
            byte dkey[1<<8][1<<8];
            std::memcpy(ekey, keyBytes, sizeof(ekey));
            std::memcpy(dkey, keyBytes, sizeof(dkey)); // NOTE without inverse
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                encrypt1_8x8(workBytes, ekey);
            } end = now();
            encDurations8["netcip1_8x8"] += (end - start).count();

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                decipher1_8x8(workBytes, dkey);
            } end = now();
            decDurations8["netcip1_8x8"] += (end - start).count();

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                encrypt1_8x8(workBytes, ekey);
                decipher1_8x8(workBytes, dkey);
            } end = now();
            durations8["netcip1_8x8"] += (end - start).count();
        }

        { // 8
            byte ekey[1<<8][1<<8];
            byte dkey[1<<8][1<<8];
            std::memcpy(ekey, keyBytes, sizeof(ekey));
            std::memcpy(dkey, keyBytes + std::size(ekey), sizeof(dkey));
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                encrypt2_8x8(workBytes, ekey);
            } end = now();
            encDurations8["netcip2_8x8"] += (end - start).count();

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                decipher2_8x8(workBytes, dkey);
            } end = now();
            decDurations8["netcip2_8x8"] += (end - start).count();

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                encrypt2_8x8(workBytes, ekey);
                decipher2_8x8(workBytes, dkey);
            } end = now();
            durations8["netcip2_8x8"] += (end - start).count();
        }

        { // 16
            byte ekey[1<<8][1<<8];
            byte dkey[1<<8][1<<8];
            std::memcpy(ekey, keyBytes, sizeof(ekey));
            std::memcpy(dkey, keyBytes + sizeof(ekey), sizeof(dkey));
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                encrypt1_8x16(workBytes, ekey);
            } end = now();
            encDurations16["netcip1_8x16"] += (end - start).count();

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                decipher1_8x16(workBytes, dkey);
            } end = now();
            decDurations16["netcip1_8x16"] += (end - start).count();

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                encrypt1_8x16(workBytes, ekey);
                decipher1_8x16(workBytes, dkey);
            } end = now();
            durations16["netcip1_8x16"] += (end - start).count();
        }

        { // 16
            byte ekey[1<<8][1<<8];
            byte dkey[1<<8][1<<8];
            std::memcpy(ekey, keyBytes, sizeof(ekey));
            std::memcpy(dkey, keyBytes + sizeof(ekey), sizeof(dkey));
            std::memcpy(workBytes, bytesSrc, sizeof(workBytes));

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                encrypt2_8x16(workBytes, ekey);
            } end = now();
            encDurations16["netcip2_8x16"] += (end - start).count();

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                decipher2_8x16(workBytes, dkey);
            } end = now();
            decDurations16["netcip2_8x16"] += (end - start).count();

            start = now(); for (cycle = 0; cycle < CYCLES; ++cycle) {
                encrypt2_8x16(workBytes, ekey);
                decipher2_8x16(workBytes, dkey);
            } end = now();
            durations16["netcip2_8x16"] += (end - start).count();
        }
    }

    std::cout << std::endl;

    auto report = [](
        const std::map<std::string, double>& encDurations,
        const std::map<std::string, double>& decDurations,
        const std::map<std::string, double>& encDecDurations,
        const std::string& blockSize
    ) {

        std::vector<std::string> ciphers;

        for (const auto& [cipher, duration] : encDurations) {
            ciphers.push_back(cipher);
        }

        std::cout << std::left
                << std::setw(2) << blockSize << std::setw(28) << " bytes" << " | "
                << std::setw(15) << "Enc Blocks/min" << " | "
                << std::setw(15) << "Dec Blocks/min" << " | "
                << std::setw(15) << "Enc-Dec Blocks/min" << "\n";
        std::cout << std::string(80, '-') << "\n"; // Разделитель

        for (const auto& cipher : ciphers) {
            double encDuration = encDurations.at(cipher);
            double decDuration = decDurations.at(cipher);
            double encDecDuration = encDecDurations.at(cipher);

            double encBlocksPerMinute = (60.0 * 1e6 * CYCLES) / encDuration;
            double decBlocksPerMinute = (60.0 * 1e6 * CYCLES) / decDuration;
            double encDecBlocksPerMinute = (60.0 * 1e6 * CYCLES) / encDecDuration;

            std::cout << std::left << std::setw(30) << cipher << " | "
                    << std::setw(15) << encBlocksPerMinute << " | "
                    << std::setw(15) << decBlocksPerMinute << " | "
                    << std::setw(15) << encDecBlocksPerMinute << "\n";
        }
        std::cout << std::endl;
    };

    report(encDurations8, decDurations8, durations8, "8");
    report(encDurations16, decDurations16, durations16, "16");
    std::cout << "crypto++: " << CryptoPP::LibraryVersion() << std::endl;

    return 0;
}
