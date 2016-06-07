#include "my_random.hpp"

MyRandom::MyRandom(unsigned int seed)
{
  word = ((unsigned long)seed << (unsigned long)(sizeof(int) * 4u)) + seed;
}

void	MyRandom::step()
{
  word = (word * 982449707ul) % 2147483647;
}

template<>
unsigned int	MyRandom::next()
{
  word = ((word & 0xFFFFFFFF) * 982449707ul);
  return (word & 0xFFFFFFFF);
}

template<>
unsigned long	MyRandom::next()
{
  word = ((word & 0xFFFFFFFF) * 982449707ul);
  return (((unsigned long)next<unsigned int>() << 32l)
	  | (unsigned long)next<unsigned int>());
}
