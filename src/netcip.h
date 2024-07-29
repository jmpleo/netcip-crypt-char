#ifndef NETCIP_H
#define NETCIP_H

#include "block.h"
#include "key.h"
#include "net.h"

struct NetCip
{
    struct Param : public Table, public Network { };

    struct Enc : public Transform, public Param { void ProcessBlock(Block &block); };
    struct Dec : public Transform, public Param { void ProcessBlock(Block &block); };
};


#endif
