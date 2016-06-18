#include "logic.hpp"
#include "fixture.hpp"

Logic::Logic() : fixtures()
{
}

void Logic::addFixture(Fixture *fixture)
{
  fixtures.push_back(fixture);
}

void Logic::removeFixture(Fixture *fixture)
{
  unsigned int i;

  i = 0;
  while (fixtures[i] != fixture)
    i = i + 1;
  fixtures.erase(fixtures.begin() + i);
}
