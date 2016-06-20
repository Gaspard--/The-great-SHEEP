#ifndef PHYSICS_HPP_
# define PHYSICS_HPP_

# include <cmath>
# include <iostream>

# include "vect.hpp"

class Fixture;

namespace	physics
{
  double	collisionTest(Fixture *fixture, double max);
  double	collisionTest(Fixture *fixture, Vect<2u, double>& point, double max);
  double	collisionTest(Fixture *fixture, Fixture *b, double max);
};

#endif // !PHYSICS_HPP_
