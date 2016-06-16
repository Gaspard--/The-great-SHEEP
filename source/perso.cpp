#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <iostream>
#include "top_header.hpp"
#include "game.hpp"
#include "perso.hpp"

//
// Constructor/Destructor
//
Perso::Perso(Game *game)
{
  SDL_Texture	*texture;
  int	x;
  int	y;

  // Load perso.png
  texture = IMG_LoadTexture(game->getRenderer(), "assets/perso.png");
  if (!texture)
    {
      std::cerr << "Failed to load image : " << SDL_GetError() << std::endl;
      exit(-1);
    }
  SDL_QueryTexture(texture, NULL, NULL, &x, &y);

  // Add renderable
  this->renderable.push_back(Renderable(new Vect<2, double>(x, y), new Vect<2, double>(x, y), texture));

  // Set booleans
  moving = false;
  selected = true;

  // Set perso position
  position = Vect<2, double>(game->getWindowWidth() / 2.0, game->getWindowHeight() / 2.0);
  destination = 0;
  direction = perso::DIR_MAX;
}

Perso::~Perso()
{
  SDL_DestroyTexture(renderable[0].texture);
}

//
// Getters
//
std::vector<Renderable> const &	Perso::getRenderable() const
{
  return (renderable);
}

Vect<2, double>			Perso::getPosition() const
{
  return (position);
}

bool				Perso::isMoving() const
{
  return (moving);
}

bool				Perso::isSelected() const
{
  return (selected);
}

//
// Setters
//
void		Perso::select()
{
  selected = true;
}

//
// Update perso
//
void		Perso::update()
{
  if (!selected || !moving)
    return;
  position = Vect<2, double>(position[0] + moveDir[0] * PERSO_SPEED,
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
void		Perso::moveTo(Vect<2, double> dest)
{
  moving = true;
  destination = dest;
  distance = sqrt(pow(destination[0] - position[0], 2) +
		  pow(destination[1] - position[1], 2));
  if (distance <= 0)
    {
      moving = false;
      return;
    }
  moveDir = Vect<2, double>((destination[0] - position[0]) / distance,
			     (destination[1] - position[1]) / distance);
  startPos = position;
}
