#ifndef OBJECT_HPP_
# define OBJECT_HPP_

# include "entity.hpp"
# include "vect.hpp"
# include "fixture.hpp"
# include "renderable.hpp"
# include "follow.hpp"
# include "display.hpp"

class PlayState;

class Object : public Entity
{
protected:
  Vect<2u, double> position;
  Vect<2u, double> speed;
  double size;
  Vect<2u, double> dimensions;
  Vect<2u, double> sizedDimensions;
  Follower<Fixture> fixture;
  Follower<Renderable> renderable;
public:
  Object(Vect<2u, double> position, double size, Vect<2u, double> dimensions, PlayState &playState);
  virtual ~Object(void);

  void update(void);
};

#endif // !OBJECT_HPP_
