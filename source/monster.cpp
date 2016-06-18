#include "monster.hpp"
#include "playstate.hpp"
#include "fixture.hpp"
#include "renderable.hpp"
#include "logic.hpp"
#include "entity_handler.hpp"

Monster::Monster(Vect<2u, double> nposition, PlayState *playState)
  : Entity(playState)
{
  speed = new Vect<2u, double>(0.0, 0.0);
  position = new Vect<2u, double>(nposition);
  size = new double(1.0);
  dimensions = new Vect<2u, double>(*size, *size);

  fixture = new Fixture(this->position, speed, size);
  renderable = new Renderable(position, dimensions, NULL);
  playState->getLogic()->addFixture(fixture);
  playState->getEntityHandler()->addEntity(this);
}

void Monster::update()
{

}

Monster::~Monster()
{
  playState->getLogic()->removeFixture(fixture);
  playState->getEntityHandler()->removeEntity(this);
  delete fixture;
  delete renderable;
  delete position;
  delete speed;
  delete size;
  delete dimensions;
}
