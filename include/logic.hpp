#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include "followable_vector.hpp"
# include "fixture.hpp"

class Logic
{
public:
  FollowableVector<Fixture> fixtures;
  Logic();
  void collision(Fixture &A, Fixture &B);
  void tick();
};

#endif // !LOGIC_HPP_
