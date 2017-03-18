#include "object.hpp"
#include "playstate.hpp"
#include "fixture.hpp"
#include "logic.hpp"
#include "entity_handler.hpp"

Object::Object(Vect<2u, double> position, double size, Vect<2u, double> dimensions, PlayState &playState)
  : Entity(playState), position(position), speed(0, 0), size(size), dimensions(dimensions),
    sizedDimensions(dimensions * size * 2),
    renderable()
{
  playState.getDisplay().renderables(renderable, this->position, sizedDimensions, nullptr);
  playState.getLogic().fixtures(fixture, this->position, this->speed, this->size);
  playState.getEntityHandler().addEntity(this);
}

void Object::update()
{
}

Object::~Object()
{
  playState.getEntityHandler().removeEntity(this);
}
