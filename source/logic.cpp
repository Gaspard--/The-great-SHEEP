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
  {
    unsigned int i(0u);

    while (i < fixtures.size())
      {
	fixtures[i]->t = 1.0;
	i = i + 1u;
      }
  }
  {
    unsigned int i(0u);
    
    while (i < fixtures.size() - 1u)
      {
	unsigned int j(i + 1u);

	while (j < fixtures.size())
	  {
	    if (fixtures[i]->t < fixtures[j]->t)
	      collision(*fixtures[i], *fixtures[j]);
	    else
	      collision(*fixtures[j], *fixtures[i]);
	    j = j + 1u;
	  }
	i = i + 1u;
      }
  }
  {
    unsigned int i(0u);

    while (i < fixtures.size())
      {
	fixtures[i]->position += fixtures[i]->speed * fixtures[i]->t;
	if (fixtures[i]->t != 1.0)
	  fixtures[i]->speed = Vect<2u, double>(0.0, 0.0);
	i = i + 1u;
      }
  }
}

void Logic::addFixture(Fixture *fixture)
{
  fixtures.push_back(fixture);
}

void Logic::removeFixture(Fixture *fixture)
{
  unsigned int i(0);

  while (fixtures[i] != fixture)
    i = i + 1;
  fixtures.erase(fixtures.begin() + i);
}
