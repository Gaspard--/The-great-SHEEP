#ifndef PERSO_HPP_
# define PERSO_HPP_

# include "entity.hpp"

// TMP
# define _TILE_WIDTH_ 60
# define _TILE_HEIGHT_ 30

/*
** Class Perso Derived from Entity: Main Perso
*/
class Perso: public Entity
{
public:
  // Constructor/Destructor
  ~Perso() {};
  void				init();
  void				destroy();

  std::vector<Renderable>	getRenderable();
  Vect<2u, double>		getPosition();
  //  void			getStats(); TODO
  //  std::vector<Fixture>	getFixtures(); TODO

  // Update perso
  void				update();

  // Move to given position
  void				moveTo(Vect<2u, double>& dest);

  // Get bool
  bool				isMoving();
  bool				isSelected();

private:
  // What to render
  std::vector<Renderable>	renderable;

  // Perso's position/destination on WORLD MAP
  Vect<2u, double>		position;
  Vect<2u, double>		destination;

  bool				moving;
  bool				selected;
};

#endif /* !PERSO_HPP_ */
