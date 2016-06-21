#include "random.hpp"

Random::Random(uint64_t x) : x(x)
{
}

uint64_t Random::next()
{
  x ^= x >> 12;
  x ^= x << 25;
  x ^= x >> 27;
  return (x * uint64_t(2685821657736338717));
}
