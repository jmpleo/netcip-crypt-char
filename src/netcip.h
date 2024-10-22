#pragma once

#include "block.h"
#include "key.h"
#include "net.h"


struct NetCip
    : protected Block
    , protected Table
    , protected Network
{
    NetCip() {}
    void UpdateKey() { SetRandomTable(); }
    std::string HexKey() { return Table::HexEncKey(); }
    std::string HexNet() { return Network::HexNet(); }

    virtual void ProcessBlock(Block &block) {};
};


struct Enc : public NetCip
{
    void ProcessBlock(Block &block) override;
};


struct Dec : public NetCip
{
    void ProcessBlock(Block &block) override;
};

