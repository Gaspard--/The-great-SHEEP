#include <algorithm>
#include "logic.hpp"
#include "fixture.hpp"
#include "physics.hpp"

Logic::Logic() : fixtures()
{
}

void	Logic::collision(Fixture &A, Fixture &B)
{
  double t(physics::collisionTest(A, B, A.t));

  if (t < A.t)
    {
      A.t = t;
      B.t = t;
    }
}

void	Logic::tick()
{
  std::for_each(fixtures.begin(), fixtures.end(), [](Followable<Fixture> &f)
		{
		  f->t = 1.0;
		});
  for (auto f(fixtures.begin()); f < fixtures.end() - 1; ++f)
    {
      for (auto g(f + 1); g < fixtures.end(); ++g)
	{
	  if ((*f)->t < (*g)->t)
	    collision(**f, **g);
	  else
	    collision(**g, **f);
	}
    }
  std::for_each(fixtures.begin(), fixtures.end(), [](Followable<Fixture> &f)
		{
		  f->position += f->speed * f->t;
		  if (f->t != 1.0)
		    f->speed = Vect<2u, double>(0.0, 0.0);
		});
}
