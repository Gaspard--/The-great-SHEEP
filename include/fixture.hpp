#ifndef FIXTURE_HPP_
# define FIXTURE_HPP_

# include "vect.hpp"

class			Fixture
{
public:
  Fixture(Vect<2u, double> *position, double *size);
  Vect<2u, double>	*position;
  double		*size;
};

#endif // FIXTURE_HPP_
