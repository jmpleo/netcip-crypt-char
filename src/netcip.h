#pragma once

#include "block.h"
#include "key.h"
#include "net.h"


struct NetCip
    : protected Block
    , protected Key
    , protected Network
{
    NetCip() {}
    void UpdateKey() { Key::SetRandomTable(); }
    void SaveKey(const char * f) { Key::SaveTable(f); }
    void LoadKey(const char * f) { Key::LoadTable(f); }
    std::string HexKey() { return Key::HexEncKey(); }
    std::string NetScheme() { return Network::NetScheme(); }

    void ProcessBlock(Block &block) {};
    void ProcessBlock(byte * block) {};
};


struct Enc : public NetCip
{
    void ProcessBlock(Block &block);
    void ProcessBlock(byte * block);
};


struct Dec : public NetCip
{
    void ProcessBlock(Block &block);
    void ProcessBlock(byte * block);
};

