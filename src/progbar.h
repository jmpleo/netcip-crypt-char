#pragma once

#include <cstddef>
#include <ostream>
#include <sys/types.h>

template <size_t With=50>
struct ProgressBar
{
    ProgressBar ();
    inline void Show (float progress, std::ostream&, const char* info="");

private:
    char bar_[With + 1];
};


template <size_t With>
ProgressBar<With>::ProgressBar () { bar_[With] = 0; }

template <size_t With>
inline void ProgressBar<With>::Show ( float progress,
                                      std::ostream& stream,
                                      const char* info )
{
    size_t i = 0;

    for (; i < progress * With; bar_[i] = '#', ++i) { }
    for (; i < With;            bar_[i] = '.', ++i) { }

    stream
        << "[" << bar_ << "] "
        << static_cast<int>(progress * 100) << "% "
        << info << "\r";

    stream.flush();
}

