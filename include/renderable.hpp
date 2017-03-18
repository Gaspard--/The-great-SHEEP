#ifndef RENDERABLE_HPP_
# define RENDERABLE_HPP_

# include <SDL2/SDL.h>
# include <new>

# include "vect.hpp"

class Texture;

struct Renderable
{
// public:
  Renderable(Vect<2u, double> &position, Vect<2u, double> &dimensions, Texture *texture);
  Renderable &operator=(Renderable const &other)
  {
    new (this) Renderable(other);
    return (*this);
  }
  Vect<2u, double> &position;
  Vect<2u, double> &dimensions;
  SDL_Rect *srcRect;
  Texture  *texture;
};

#endif // !RENDERABLE_HPP_
