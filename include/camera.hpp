#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# include "vect.hpp"
# include "top_header.hpp"

class Camera
{
private:
  Vect<2, double> position;
public:
  constexpr Camera(void)
    : position(TILE_DIM / 2, TILE_DIM / 2)
  {
  }

  Vect<2u, double> getPosition(void) const;

  void	setPosition(const Vect<2u, double> &position);

  void	move(Vect<2u, double> &offset);

  Vect<2u, int> getFlooredCamera(void) const;

  constexpr Vect<2u, double> fullIsometrize(Vect<2u, double> const &in) const
  {
    Vect<2u, double> const relative(in - position);

    return ((relative + Vect<2u, double>(-relative[1], relative[0])) * Vect<2u, double>(60.0, 30.0));
  }

  constexpr Vect<2u, double> fullDesisometrize(Vect<2u, double> const &in) const
  {
    Vect<2u, double> const tmp(in * Vect<2u, double>(1.0 / 60.0, 1.0 / 30.0));

    return ((tmp + Vect<2u, double>(tmp[1], -tmp[0])) * 0.5 + position);
  }
};

#endif // !CAMERA_HPP_
