#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <vector>

class Fixture;
class Renderable;
class PlayState;

class Entity
{
private:
  PlayState *playState;
public:
  Entity(PlayState *playState);
  virtual ~Entity(void);
  virtual void update(void) = 0;
};

#endif // !ENTITY_HPP_
