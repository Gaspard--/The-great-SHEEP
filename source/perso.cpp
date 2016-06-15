#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "top_header.hpp"
#include "perso.hpp"

Perso::Perso(SDL_Renderer *renderer)
{
  SDL_Texture	*texture;
  int	x;
  int	y;

  // Load perso.png
  texture = IMG_LoadTexture(renderer, "assets/perso.png");
  if (!texture)
    {
      std::cerr << "Failed to load image : " << SDL_GetError() << std::endl;
      exit(-1);
    }
  SDL_QueryTexture(texture, NULL, NULL, &x, &y);

  // Add renderable
  Vect<2u, double>	*pos = new Vect<2u, double>((double)x, (double)y);
  Vect<2u, double>	*dim = new Vect<2u, double>((double)x, (double)y);
  Renderable		renderable = Renderable(pos, dim, texture);

  this->renderable.push_back(renderable);

  // Set booleans
  moving = false;
  selected = true;

  // Set perso position
  position = Vect<2u, double>(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
  destination = 0;
  direction = perso::DIR_MAX;
}

Perso::~Perso()
{
  delete renderable[0].position;
  delete renderable[0].dimensions;
  SDL_DestroyTexture(renderable[0].texture);
}
