#ifndef ENTITY_HPP_
# define ENTITY_HPP_

// class Fixture; TODO
class Renderable;

class Entity
{
public:
  virtual ~Entity(){};
  //  virtual std::vector<Fixture>	getFixtures() = 0; TODO
  virtual std::vector<Renderable>	getRenderable() = 0;
  virtual void				update() = 0;
  //  virtual void			getStats() = 0; TODO
};

#endif // !ENTITY_HPP_
