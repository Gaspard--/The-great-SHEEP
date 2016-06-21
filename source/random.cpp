#include "random.hpp"

uint64_t my_random::randomFrom(uint64_t x)
{
  return (Random((Random(Random(x).next()).next())).next());
}

uint64_t my_random::randomFrom(Vect<2u, uint32_t> vec)
{
  return (my_random::randomFrom(vec[0] | vec[1] * ((1ul << 32ul) - 1)));
}

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
