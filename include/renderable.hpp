#ifndef RENDERABLE_HPP_
# define RENDERABLE_HPP_

# include <SDL2/SDL.h>

# include "vect.hpp"

class Texture;

class Renderable
{
public:
  Renderable(Vect<2u, double> &position, Vect<2u, double> &dimensions, Texture *texture);

  Vect<2u, double> &position;
  Vect<2u, double> &dimensions;
  SDL_Rect *srcRect;
  Texture  *texture;
};

#endif // !RENDERABLE_HPP_
