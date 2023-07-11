#ifndef FIXEDPARAM_H
#define FIXEDPARAM_H


template <unsigned int N, unsigned int M>
struct FixedBlockParam
{
    static const int SUBBLOCKSIZE = N;
    static const int NUMSUBBLOCKS = M;
};
template <unsigned int S>
struct FixedBlockSize
{
    static const int BLOCKSIZE = S;
};
template <unsigned int R>
struct FixedRounds
{
    static const int ROUNDS = R;
};

#endif
