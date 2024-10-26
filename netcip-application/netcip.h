#include <cstdint>

using byte = std::uint8_t;

/**
 * Application Cipher Implementations
 */
inline void encrypt1_8x8(byte block[8], byte ekey[1<<8][1<<8])
{
    #define C(i, j) ( block[j] = ekey[ block[i] ][ block[j] ] )

    C(0,1);
    C(1,2);
    C(2,3);
    C(3,4);
    C(4,5);
    C(5,6);
    C(6,7);

    C(7,0);

    C(6,7);
    C(5,6);
    C(4,5);
    C(3,4);
    C(2,3);
    C(1,2);
    C(2,1);

    #undef C
}


inline void decipher1_8x8(byte block[8], byte dkey[1<<8][1<<8])
{
    #define C(i, j) ( block[j] = dkey[ block[i] ][ block[j] ] )

    C(2,1);
    C(1,2);
    C(2,3);
    C(3,4);
    C(4,5);
    C(5,6);
    C(6,7);
    C(7,0);
    C(6,7);
    C(5,6);
    C(4,5);
    C(3,4);
    C(2,3);
    C(1,2);
    C(0,1);

    #undef C
}


inline void encrypt2_8x8(byte block[8], byte ekey[1<<8][1<<8])
{
    #define C(i, j) ( block[j] = ekey[ block[i] ][ block[j] ] )

    C(0,7);
    C(7,0);
    C(1,7);
    C(7,1);
    C(2,7);
    C(7,2);
    C(3,7);
    C(7,3);
    C(4,7);
    C(7,4);
    C(5,7);
    C(7,5);
    C(6,7);
    C(7,6);
    C(6,7);

    #undef C
}


inline void decipher2_8x8(byte block[8], byte dkey[1<<8][1<<8])
{
    #define C(i, j) ( block[j] = dkey[ block[i] ][ block[j] ] )

    C(6,7);
    C(7,6);
    C(6,7);
    C(7,5);
    C(5,7);
    C(7,4);
    C(4,7);
    C(7,3);
    C(3,7);
    C(7,2);
    C(2,7);
    C(7,1);
    C(1,7);
    C(7,0);
    C(0,7);

    #undef C
}


inline void encrypt1_8x16(byte block[16], byte ekey[1<<8][1<<8])
{
    #define C(i, j) ( block[j] = ekey[ block[i] ][ block[j] ] )

    C(0,1);
    C(1,2);
    C(2,3);
    C(3,4);
    C(4,5);
    C(5,6);
    C(6,7);
    C(7,8);
    C(8,9);
    C(9,10);
    C(10,11);
    C(11,12);
    C(12,13);
    C(13,14);
    C(14,15);

    C(15,0);

    C(14,15);
    C(13,14);
    C(12,13);
    C(11,12);
    C(10,11);
    C(9,10);
    C(8,9);
    C(7,8);
    C(6,7);
    C(5,6);
    C(4,5);
    C(3,4);
    C(2,3);
    C(1,2);
    C(2,1);

    #undef C
}


inline void decipher1_8x16(byte block[16], byte dkey[1<<8][1<<8])
{
    #define C(i, j) ( block[j] = dkey[ block[i] ][ block[j] ] )

    C(2,1);
    C(1,2);
    C(2,3);
    C(3,4);
    C(4,5);
    C(5,6);
    C(6,7);
    C(7,8);
    C(8,9);
    C(9,10);
    C(10,11);
    C(11,12);
    C(12,13);
    C(13,14);
    C(14,15);
    C(15,0);
    C(14,15);
    C(13,14);
    C(12,13);
    C(11,12);
    C(10,11);
    C(9,10);
    C(8,9);
    C(7,8);
    C(6,7);
    C(5,6);
    C(4,5);
    C(3,4);
    C(2,3);
    C(1,2);
    C(0,1);

    #undef C
}


inline void encrypt2_8x16(byte block[16], byte ekey[1<<8][1<<8])
{
    #define C(i, j) ( block[j] = ekey[ block[i] ][ block[j] ] )

    C(0, 15);
    C(15, 0);
    C(1, 15);
    C(15, 1);
    C(2, 15);
    C(15, 2);
    C(3, 15);
    C(15, 3);
    C(4, 15);
    C(15, 4);
    C(5, 15);
    C(15, 5);
    C(6, 15);
    C(15, 6);
    C(7, 15);
    C(15, 7);
    C(8, 15);
    C(15, 8);
    C(9, 15);
    C(15, 9);
    C(10,15);
    C(15,10);
    C(11,15);
    C(15,11);
    C(12,15);
    C(15,12);
    C(13,15);
    C(15,13);
    C(14,15);
    C(15,14);
    C(14,15);

    #undef C
}


inline void decipher2_8x16(byte block[16], byte dkey[1<<8][1<<8])
{
    #define C(i, j) ( block[j] = dkey[ block[i] ][ block[j] ] )

    C(14,15);
    C(15,14);
    C(14,15);
    C(15,13);
    C(13,15);
    C(15,12);
    C(12,15);
    C(15,11);
    C(11,15);
    C(15,10);
    C(10,15);
    C(15, 9);
    C(9, 15);
    C(15, 8);
    C(8, 15);
    C(15, 7);
    C(7, 15);
    C(15, 6);
    C(6, 15);
    C(15, 5);
    C(5, 15);
    C(15, 4);
    C(4, 15);
    C(15, 3);
    C(3, 15);
    C(15, 2);
    C(2, 15);
    C(15, 1);
    C(1, 15);
    C(15, 0);
    C(0, 15);

    #undef C
}

