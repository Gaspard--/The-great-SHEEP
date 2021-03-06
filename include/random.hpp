#ifndef RANDOM_HPP_
# define RANDOM_HPP_

# include <cstdint>
# include "vect.hpp"

namespace my_random
{
};

class Random
{
private:
  uint64_t seed;
  uint64_t x;
public:
  Random(uint64_t seed);
  uint64_t randomFrom(uint64_t source);
  uint64_t randomFrom(Vect<2u, uint32_t> source);
  uint64_t next();
};

#endif // !RANDOM_HPP_
