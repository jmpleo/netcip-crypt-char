#include "wa-coef.cpp"

#include <cstdint>
#include <ctime>
#include <iostream>
#include <numeric>
#include <ostream>
#include <random>
#include <type_traits>
#include <vector>

int main() {
  const int len = 16;

  int64_t vecf[len];

  std::random_device d;

  for (int i = 0; i < len; ++i) {
    std::bernoulli_distribution dist(0.8);
    std::cout << (int)(vecf[i]=dist(d)) << " ";
  } std::cout << std::endl;

  FFT(vecf, len);
  for (int i = 0; i < len; ++i) {
    std::cout << (int)vecf[i] << " ";
  }
  std::cout << "sum: " << std::accumulate(
    vecf, vecf + 16, 0., [](auto sum, auto a){ return sum + (double)(a*a); }
  ) << std::endl;

}
