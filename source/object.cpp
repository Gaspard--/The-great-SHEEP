#include "object.hpp"
#include "playstate.hpp"
#include "fixture.hpp"
#include "logic.hpp"
#include "entity_handler.hpp"

Object::Object(Vect<2u, double> nposition, int nsize, Vect<2u, double> ndimensions, PlayState *playState)
  : Entity(playState), position(nposition), speed(0, 0), size(nsize), dimensions(ndimensions),
    fixture(&position, &speed, &size), renderable(&position, &dimensions, NULL)
{
  playState->getLogic().addFixture(&fixture);
  playState->getDisplay().addRenderable(&renderable);
  playState->getEntityHandler().addEntity(this);
}

void Object::update()
{
}

Object::~Object()
{
  playState->getLogic().removeFixture(&fixture);
  playState->getDisplay().removeRenderable(&renderable);
  playState->getEntityHandler().removeEntity(this);
}
