#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "top_header.hpp"
#include "perso.hpp"

//
// Constructor/Destructor
//
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

  this->renderable.push_back(Renderable(pos, dim, texture));

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

//
// Getters
//
std::vector<Renderable>		Perso::getRenderable()
{
  return (renderable);
}

Vect<2u, double>		Perso::getPosition()
{
  return (position);
}

bool				Perso::isMoving()
{
  return (moving);
}

bool				Perso::isSelected()
{
  return (selected);
}

//
// Update perso
//
void		Perso::update()
{
  if (!selected || !moving)
    return;
  position = Vect<2u, double>(position[0] + moveDir[0] * PERSO_SPEED,
			      position[1] + moveDir[1] * PERSO_SPEED);
  if (sqrt(pow(position[0] - startPos[0], 2) + pow(position[1] - startPos[1], 2)) >= distance)
    {
      position = destination;
      moving = false;
    }
}

//
// Move to Position
//
void		Perso::moveTo(Vect<2u, double>& dest)
{
  if (position[0] == dest[0] && position[1] == dest[1])
    return;
  moving = true;
  destination = dest;
  distance = sqrt(pow(destination[0] - position[0], 2) +
		  pow(destination[1] - position[1], 2));
  moveDir = Vect<2u, double>((destination[0] - position[0]) / distance,
			     (destination[1] - position[1]) / distance);
  startPos = position;
}
