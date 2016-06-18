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
  : Entity(playState), position(startPosition)
{

  // Load perso.png
  textures[perso::DIR_IDLE] = IMG_LoadTexture(game->getRenderer(), "assets/perso.png");
  textures[perso::DIR_RIGHT] = IMG_LoadTexture(game->getRenderer(), "assets/right.png");
  textures[perso::DIR_LEFT] = IMG_LoadTexture(game->getRenderer(), "assets/left.png");
  if (!textures[perso::DIR_IDLE] || !textures[perso::DIR_RIGHT] || !textures[perso::DIR_LEFT])
    {
      std::cerr << "Failed to load image : " << SDL_GetError() << std::endl;
      exit(-1);
    }

  // Add renderable
  renderable = new Renderable(&position,
			      new Vect<2, double>(PERSO_WIDTH, PERSO_HEIGHT),
			      textures[perso::DIR_IDLE]);
  renderable->srcRect = NULL;
  playState->getDisplay()->addRenderable(renderable);

  // Set booleans
  moving = false;
  selected = true;

  // Set perso position
  destination = 0;
  direction = perso::DIR_MAX;

  // Set sprites
  frame = 0;
  int	i;
  i = 0;
  while (i < PERSO_NB_FRAME)
    {
      sprites[i].x = i * 60;
      sprites[i].y = 0;
      sprites[i].w = 60;
      sprites[i].h = 100;
      i = i + 1;
    }
}

Perso::~Perso()
{
  int	i;

  playState->getDisplay()->removeRenderable(renderable);
  delete renderable->dimensions;
  delete renderable;
  i = perso::DIR_IDLE;
  while (i < perso::DIR_MAX)
    {
      SDL_DestroyTexture(textures[i]);
      i = i + 1;
    }
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
  position = position + speed * PERSO_SPEED;
  if (distance <= 0)
    {
      *renderable->dimensions = Vect<2, double>(PERSO_WIDTH, PERSO_HEIGHT);
      // Set IDLE sprite
      renderable->texture = textures[perso::DIR_IDLE];
      moving = false;
    }
  if (moving)
    renderable->srcRect = sprites + frame / PERSO_FRAME_SPEED;
  else
    renderable->srcRect = NULL;
}

//
// Move to Position
//
void		Perso::moveTo(Vect<2, double> dest)
{
  frame = 0;
  moving = true;
  destination = dest;
  if (destination[0] >= position[0])
    direction = perso::DIR_RIGHT;
  else
    direction = perso::DIR_LEFT;

  // Set sprite accordingly to direction
  renderable->texture = textures[direction];
  distance = sqrt(pow(destination[0] - position[0], 2) +
  		  pow(destination[1] - position[1], 2));
  if (distance <= 0)
    {
      moving = false;
      return;
    }
  speed = Vect<2, double>((destination[0] - position[0]) / distance,
			  (destination[1] - position[1]) / distance);
}

void		Perso::render(Game *game) const
{
  SDL_Rect	rect;

  rect.w = PERSO_WIDTH;
  rect.h = PERSO_HEIGHT;
  rect.x = game->getWindowWidth() / 2 - rect.w / 2;
  rect.y = game->getWindowHeight() / 2 - rect.h;
  if (!moving)
    SDL_RenderCopy(game->getRenderer(), renderable->texture, NULL, &rect);
  else
    SDL_RenderCopy(game->getRenderer(), renderable->texture, &sprites[frame / PERSO_FRAME_SPEED], &rect);
}
