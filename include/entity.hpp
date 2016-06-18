#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <vector>

class Fixture;
class Renderable;
class PlayState;
class Game;

class Entity
{
protected:
  PlayState *playState;
public:
  Entity();
  Entity(PlayState *playState);
  virtual ~Entity(void);
  virtual void update(void) = 0;
  virtual void render(Game *game) const = 0;
};

#endif // !ENTITY_HPP_
