#include "physics.hpp"
#include "fixture.hpp"

// |Vt + P| == r
// V\2t\2 + P\2 + V.Pt - r = 0
// Equation de degré 2:
//

double		physics::collisionTest(Fixture &fixture, double max)
{
  if (fixture.position.scalar(fixture.speed) > 0.0)
    return (max);
  double	a(fixture.speed.scalar(fixture.speed));
  double	b(fixture.speed.scalar(fixture.position));
  double	c(fixture.position.scalar(fixture.position) - fixture.size / 2);
  double	delta(b * b - 4 * a * c);

  if (delta < 0)
    return (max);
  if (delta == 0)
    return (-b * 0.5 / a);
  delta = sqrt(delta);
  return (std::min((-b + delta) * 0.5 / a, (-b - delta) * 0.5 / a));
}

double		physics::collisionTest(Fixture &fixture, Vect<2u, double>& point, double max)
{
  Vect<2u, double>	position(fixture.position - point);
  Fixture		tmp(position, fixture.speed, fixture.size);

  return (collisionTest(tmp, max));
}

double		physics::collisionTest(Fixture &fixture, Fixture &other, double max)
{
  Vect<2u, double>	position(fixture.position - other.position);
  Vect<2u, double>	speed(fixture.speed - other.speed);
  double		size(fixture.size + other.size);
  Fixture		tmp(position, speed, size);

  return (collisionTest(tmp, max));
}
