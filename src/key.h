#ifndef KEY_H
#define KEY_H

#include "types.h"
#include "block.h"


/*
 * Function F(x,y) in round transformition two N-bit blocks to N-bit block
 * EncTable is a matrix, where EncTable[x][y] = F(x,y)
 * size of EncTable is (2^N * 2^N) N-bits
 */
class Table : Block
{
public:
    bool LoadTable(const char * filename);
    bool SaveTable(const char * filename);
    void SetRandomTable();

protected:
    #define TABLE_DIM (1 << Block::SUBBLOCKSIZE)
    byte encTab_[TABLE_DIM][TABLE_DIM];
    byte decTab_[TABLE_DIM][TABLE_DIM];

private:
    void GenerateTables();
};

#endif
