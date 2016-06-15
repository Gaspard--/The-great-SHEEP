#include <string>
#include <SDL2/SDL_image.h>
#include "renderable.hpp"

Renderable::Renderable(Vect<2u, double> position,
		       Vect<2u, double> dimensions,
		       SDL_Texture *texture)
  : position(position), dimensions(dimensions), texture(texture)
{
}
