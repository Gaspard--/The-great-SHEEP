#ifndef PERSO_HPP_
# define PERSO_HPP_

# include "entity.hpp"

# define PERSO_SPEED 7
# define PERSO_NB_FRAME 9

// Forward declaration
class Game;

/*
** Class Perso Derived from Entity: Main Perso
*/

namespace perso
{
  enum Direction
    {
      DIR_LEFT,
      DIR_RIGHT,
      DIR_UP,
      DIR_DOWN,
      DIR_MAX
    };
}

class Perso: public Entity
{
public:
  // Constructor/Destructor
  Perso(Game *game);
  ~Perso();

  std::vector<Renderable>&	getRenderable();
  Vect<2u, double>		getPosition();
  //  void			getStats(); TODO
  //  std::vector<Fixture>	getFixtures(); TODO

  // Update perso
  void				update();

  // Move to given position
  // TODO : PATHFINDING WORLD MAP ARRAY
  void				moveTo(Vect<2u, double> dest);

  // Get bool
  bool				isMoving();
  bool				isSelected();

  // Set bool
  void				select();

private:
  Game				*game;
  // What to render
  std::vector<Renderable>	renderable;

  // TODO : Perso's position/destination on WORLD MAP
  Vect<2u, double>		position;
  Vect<2u, double>		destination;
  Vect<2u, double>		moveDir;
  Vect<2u, double>		startPos;
  double			distance;
  // (for now screen positons)

  // TODO animated sprite
  perso::Direction		direction;

  bool				moving;
  bool				selected;
};

#endif /* !PERSO_HPP_ */
