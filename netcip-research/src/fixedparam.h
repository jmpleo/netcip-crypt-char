#pragma once

template <unsigned int N, unsigned int M>
struct FixedBlockParam
{
    static constexpr int SUBBLOCK_SIZE = N;
    static constexpr int NUM_SUBBLOCKS = M;
    static constexpr int BLOCKSIZE = N * M;
};


template <unsigned int R>
struct FixedRounds
{
    static constexpr int ROUNDS = R;
};
