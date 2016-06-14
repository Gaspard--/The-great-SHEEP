#ifndef ENTITY_HPP_
# define ENTITY_HPP_

# include <vector>
# include "renderable.hpp"

class Entity
{
public:
  virtual ~Entity() {};

  //  virtual std::vector<Fixture>	getFixtures() = 0; TODO
  virtual std::vector<Renderable>	getRenderable() = 0;
  virtual void				update() = 0;
  //  virtual void			getStats() = 0; TODO

private:
  std::vector<Renderable>		renderable;
};

#endif // !ENTITY_HPP_
