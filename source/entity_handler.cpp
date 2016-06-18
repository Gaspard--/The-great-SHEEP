#include "entity_handler.hpp"
#include "entity.hpp"
#include "playstate.hpp"

EntityHandler::EntityHandler(PlayState *playState)
  : entities(), playState(playState)
{
}

void EntityHandler::update()
{
  unsigned int i;

  i = 0;
  while (i < entities.size())
    {
      entities[i]->update();
      i = i + 1;
    }
}

void EntityHandler::addEntity(Entity *entity)
{
  entities.push_back(entity);
}

void EntityHandler::removeEntity(Entity *entity)
{
  unsigned int i;

  i = 0;
  while (entities[i] != entity)
    i = i + 1;
  entities.erase(entities.begin() + 5);
}
