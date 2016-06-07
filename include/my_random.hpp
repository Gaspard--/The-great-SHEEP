#ifndef MY_RANDOM_HPP_
# define MY_RANDOM_HPP_

class		MyRandom
{
private:
  unsigned long	word;
public:
  MyRandom(unsigned int seed);
  void	step();
  template<class T>
  T	next();
};

#endif // MY_RANDOM_HPP_
