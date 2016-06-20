#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <iostream>
#include "top_header.hpp"
#include "game.hpp"
#include "perso.hpp"
#include "playstate.hpp"

static SDL_Texture *loadTexture(Game *game, const std::string &name)
{
  std::string file_path("assets/" + name + ".png");
  return IMG_LoadTexture(game->getRenderer(), file_path.c_str());
}

//
// Constructor/Destructor
//
Perso::Perso(Game *game, PlayState *playState, Vect<2u, double> startPosition)
  : Entity(playState), position(startPosition)
{
  SDL_Texture *newTextures[directionCount] =
    {
      loadTexture(game, "perso"),
      loadTexture(game, "left"),
      loadTexture(game, "right"),
    };

  for (SDL_Texture *tex : newTextures)
    {
      if (!tex)
        {
          // TODO: Ugh.
          std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
          exit(-1);
        }
    }

  std::copy(newTextures, newTextures + directionCount, textures);

  // Add renderable
  renderable = new Renderable(&position,
			      new Vect<2, double>(PERSO_WIDTH, PERSO_HEIGHT),
			      getTexture(Direction::IDLE));
  renderable->srcRect = NULL;
  playState->getDisplay()->addRenderable(renderable);

  // Set booleans
  moving = false;
  selected = true;

  // Set perso position
  destination = 0;
  direction = Direction::MAX;

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
  playState->getDisplay()->removeRenderable(renderable);
  delete renderable->dimensions;
  delete renderable;
  for (SDL_Texture *texture : textures)
    SDL_DestroyTexture(texture);
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
      renderable->texture = getTexture(Direction::IDLE);
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
    direction = Direction::RIGHT;
  else
    direction = Direction::LEFT;

  // Set sprite accordingly to direction
  renderable->texture = getTexture(direction);
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
