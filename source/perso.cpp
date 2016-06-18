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
Perso::Perso(Game *game, Display *display) : game(game), display(display), position(display->getCamera())
{

  // Load perso.png
  idle = IMG_LoadTexture(game->getRenderer(), "assets/perso.png");
  if (!idle)
    {
      std::cerr << "Failed to load image : " << SDL_GetError() << std::endl;
      exit(-1);
    }
  int	x;
  int	y;
  SDL_QueryTexture(idle, NULL, NULL, &x, &y);

  // Add renderable
  this->renderable.push_back(Renderable(new Vect<2, double>(x, y), new Vect<2, double>(x, y), idle));

  // Set booleans
  moving = false;
  selected = true;

  // Set perso position
  destination = 0;
  direction = perso::DIR_MAX;

  // Set sprites
  frame = 0;
}

Perso::~Perso()
{
  delete renderable.back().dimensions;
  delete renderable.back().position;
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
  distance -= PERSO_SPEED;
  position[0] += speed[0] * PERSO_SPEED;
  position[1] += speed[1] * PERSO_SPEED;
  display->moveCamera(speed[0] * PERSO_SPEED, speed[1] * PERSO_SPEED);
  if (distance <= 0)
    {
      moving = false;
    }
}

//
// Move to Position
//
void		Perso::moveTo(Vect<2, double> dest)
{
  frame = 0;
  moving = true;
  destination = dest;
  distance = sqrt(pow(destination[0] - position[0], 2) +
  		  pow(destination[1] - position[1], 2));
  if (distance <= 0)
    {
      delete renderable.back().dimensions;
      delete renderable.back().position;
      renderable.clear();
      int	x;
      int	y;
      SDL_QueryTexture(idle, NULL, NULL, &x, &y);
      this->renderable.push_back(Renderable(new Vect<2, double>(x, y), new Vect<2, double>(x, y), idle));
      moving = false;
      return;
    }
  speed = Vect<2, double>((destination[0] - position[0]) / distance,
			  (destination[1] - position[1]) / distance);
}
