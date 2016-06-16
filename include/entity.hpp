#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <vector>

// class Fixture; TODO
class Renderable;

class Entity
{
public:
  virtual ~Entity(void) {};
  //  virtual std::vector<Fixture> getFixtures(void) = 0; TODO
  virtual std::vector<Renderable> &getRenderable(void) const = 0;
  virtual void update(void) = 0;
  //  virtual void getStats(void) = 0; TODO
};

#endif // !ENTITY_HPP_
