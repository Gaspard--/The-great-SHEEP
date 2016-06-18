#ifndef ENTITY_HANDLER_HPP_
# define ENTITY_HANDLER_HPP_

#include <vector>

class Entity;
class PlayState;

class EntityHandler
{
private:
  std::vector<Entity *> entities;
  PlayState *playState;
public:
  EntityHandler(PlayState *playState);
  void	update();
  void	addEntity(Entity *entity);
  void  removeEntity(Entity *entity);
};

#endif // !ENTITY_HANDLER_HPP_
