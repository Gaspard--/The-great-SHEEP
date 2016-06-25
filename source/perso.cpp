#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <iostream>
#include "top_header.hpp"
#include "game.hpp"
#include "perso.hpp"
#include "playstate.hpp"

//
// Constructor/Destructor
//
Perso::Perso(Game *game, PlayState *playState, Vect<2u, double> startPosition)
  : Object(startPosition, 0.5, Vect<2u, double>(PERSO_WIDTH, PERSO_HEIGHT), playState),
    textures
{
  Texture(game, "perso.png"),
    Texture(game, "left.png"),
    Texture(game, "right.png")
    }
{
  // Add renderable
  renderable.texture = getTexture(Direction::IDLE);
  renderable.srcRect = NULL;

  // Set booleans
  moving = false;
  selected = true;

  destination = 0;
  direction = Direction::MAX;

  // Set sprites
  frame = 0;

  {
    int	i(0);

    while (i < PERSO_NB_FRAME)
      {
	sprites[i].x = i * 60;
	sprites[i].y = 0;
	sprites[i].w = 60;
	sprites[i].h = 100;
	i = i + 1;
      }
  }
}

Perso::~Perso()
{
}

//
// Getters
//
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

  // Incremente frame
  frame += 1;
  if (frame / PERSO_FRAME_SPEED >= PERSO_NB_FRAME)
    frame = 0;

  // Decremente distance & update position
  distance -= PERSO_SPEED;
  //  position = position + speed * PERSO_SPEED;
  if (distance <= 0 || (speed[0] == 0.0 && speed[1] == 0.0))
    {
      // Set IDLE sprite
      renderable.texture = getTexture(Direction::IDLE);
      moving = false;
      speed = Vect<2u, double>(0.0, 0.0);
    }
  if (moving)
    renderable.srcRect = sprites + frame / PERSO_FRAME_SPEED;
  else
    renderable.srcRect = NULL;
}

//
// Move to Position
//
void		Perso::moveTo(Vect<2, double> dest)
{
  frame = 0;
  moving = true;
  destination = dest;
  if (destination.x() >= position.x())
    direction = Direction::RIGHT;
  else
    direction = Direction::LEFT;

  // Set sprite accordingly to direction
  renderable.texture = getTexture(direction);
  distance = sqrt(pow(destination.x() - position.x(), 2) +
  		  pow(destination.y() - position.y(), 2));
  if (distance <= 0)
    {
      moving = false;
      return;
    }
  speed = (destination - position) *  PERSO_SPEED / distance;
}
