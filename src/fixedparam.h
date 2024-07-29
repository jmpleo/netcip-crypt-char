#pragma once

template <unsigned int N, unsigned int M>
struct FixedBlockParam
{
    static constexpr int SUBBLOCKSIZE = N;
    static constexpr int NUMSUBBLOCKS = M;
};
template <unsigned int S>
struct FixedBlockSize
{
    static constexpr int BLOCKSIZE = S;
};
template <unsigned int R>
struct FixedRounds
{
    static constexpr int ROUNDS = R;
};
