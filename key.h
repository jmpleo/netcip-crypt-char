#ifndef KEY_H
#define KEY_H

#include "types.h"
#include "block.h"

#define TABLE_DIM (1 << SUBBLOCKSIZE)

class Table : Block
{
public:
    bool LoadTable(const char * filename);
    bool SaveTable(const char * filename);
    void SetRandomTable();
protected:
    byte encTab_[TABLE_DIM][TABLE_DIM];
    byte decTab_[TABLE_DIM][TABLE_DIM];
private:
    void GenerateTables();
};

#endif
