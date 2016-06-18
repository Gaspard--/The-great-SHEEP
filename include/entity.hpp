#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <vector>

class Fixture;
class Renderable;
class PlayState;

class Entity
{
public:
  virtual ~Entity(void) {};
  virtual void update(PlayState *playState) = 0;
  //  virtual void getStats(void) = 0; TODO
};

#endif // !ENTITY_HPP_
