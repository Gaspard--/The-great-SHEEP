#ifndef MONSTER_HPP_
# define MONSTER_HPP_

#include "entity.hpp"
#include "vect.hpp"

class PlayState;

class Monster : Entity
{
private:
  Fixture *fixture;
  Renderable *renderable;
  Vect<2u, double> *speed;
  Vect<2u, double> *position;
  double *size;
  Vect<2u, double> *dimensions;
public:
  Monster(Vect<2u, double> position, PlayState *playState);
  virtual ~Monster(void);

  void update(void);
};

#endif // !MONSTER_HPP_
