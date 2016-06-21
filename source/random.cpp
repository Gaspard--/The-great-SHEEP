#include "random.hpp"

uint64_t Random::randomFrom(uint64_t y)
{
  return (Random(Random(y ^ x).next() ^ x).next());
}

uint64_t Random::randomFrom(Vect<2u, uint32_t> vec)
{
  return (Random::randomFrom(vec[0] | vec[1] * ((1ul << 32ul) - 1ul)));
}

Random::Random(uint64_t seed) : seed(seed), x(seed)
{
}

uint64_t Random::next()
{
  x ^= x >> 12;
  x ^= x << 25;
  x ^= x >> 27;
  return (x * uint64_t(2685821657736338717));
}
