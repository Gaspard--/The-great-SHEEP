#ifndef PERSO_HPP_
# define PERSO_HPP_

# include <cassert>
# include <SDL2/SDL.h>
# include "object.hpp"
# include "vect.hpp"
# include "renderable.hpp"

// Perso movement speed
# define PERSO_SPEED 0.06

// Perso frame speed (lower is faster)
# define PERSO_FRAME_SPEED 3

// Perso frame number
# define PERSO_NB_FRAME 9

// Perso dimensions
# define PERSO_WIDTH 1
# define PERSO_HEIGHT 2

// Forward declaration
class Game;
class Display;

/*
** Class Perso Derived from Entity: Main Perso
*/

class Perso : public Entity
{
public:
  enum class Direction
  {
    IDLE,
    LEFT,
    RIGHT,
    MAX,
  };

  static const int directionCount = static_cast<int>(Direction::MAX);

private:

  Renderable			*renderable;

  // Perso movement
  Vect<2, double>		position;
  Vect<2, double>		destination;
  Vect<2, double>		speed;
  double			distance;

  // sprites
  SDL_Texture			*textures[directionCount];
  int				frame;
  SDL_Rect			sprites[PERSO_NB_FRAME];
  Direction                     direction;

  bool				moving;
  bool				selected;

  SDL_Texture *getTexture(Direction direction) {
    return textures[static_cast<int>(direction)];
  }

  void setTexture(Direction direction, SDL_Texture *texture) {
    assert(texture);
    textures[static_cast<int>(direction)] = texture;
  }

public:
  // Constructor/Destructor
  Perso(Game *game, PlayState *playState, Vect<2u, double> startPosition);
  ~Perso();

  Vect<2u, double>		getPosition() const;
  //  void			getStats(); TODO
  //  std::vector<Fixture>	getFixtures(); TODO

  // Update perso
  void				update();

  // Move to given position
  void				moveTo(Vect<2u, double> dest);

  // Get bool
  bool				isMoving() const;
  bool				isSelected() const;

  // Set bool
  void				select();
};

#endif /* !PERSO_HPP_ */
