#pragma once

#include "block.h"
#include "key.h"
#include "net.h"


struct NetCip : protected Block, public Key, public Network
{
    NetCip() {}

    void operator()(Block &block) {};
};


struct Enc : public NetCip
{
    void operator()(Block &block);
};


struct Dec : public NetCip
{
    void operator()(Block &block);
};


