#include "entity_handler.hpp"
#include "entity.hpp"
#include "playstate.hpp"

EntityHandler::EntityHandler(PlayState *playState) : playState(playState)
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
