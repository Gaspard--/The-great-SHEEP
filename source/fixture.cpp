#include "fixture.hpp"
#include "entity.hpp"

Fixture::Fixture(Vect<2u, double> &position, Vect<2u, double> &speed, double &size)
  : position(position), speed(speed), size(size)
{
}
