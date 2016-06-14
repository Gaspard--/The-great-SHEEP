#include "top_header.hpp"
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "object.hpp"
#include "character.hpp"

Display::Display(Game *cGame)
{
  game = cGame;

  // Load textures
  textures[display::TEXTURE_COEUR] = IMG_LoadTexture(game->renderer, "assets/icon_heart.png");
  textures[display::TEXTURE_POKEMON] = IMG_LoadTexture(game->renderer, "assets/pok.png");
  textures[display::TEXTURE_BASIC_TILESET] = IMG_LoadTexture(game->renderer, "assets/basic_tileset.png");
  textures[display::TEXTURE_BASIC_OBJECT_SET] =
    IMG_LoadTexture(game->renderer, "assets/basic_object_set.png");
  textures[display::TEXTURE_BASIC_CHARACTER_SET] =
    IMG_LoadTexture(game->renderer, "assets/basic_character_set.png");

  int		i;

  i = 0;
  while (i < display::TEXTURE_MAX)
    {
      if (!textures[i])
	{
	  fprintf(stderr, "Failed to open a texture : (%s)\n", SDL_GetError());
	  exit(-1);
	}
      i = i + 1;
    }
}

Display::~Display()
{
  int		i;

  i = 0;
  while (i < display::TEXTURE_MAX)
    {
      SDL_DestroyTexture(textures[i]);
      i = i + 1;
    }
}

void	Display::clearScreen(int r, int g, int b)
{
  SDL_SetRenderDrawColor(game->renderer, r, g, b, 255);
  SDL_RenderClear(game->renderer);
}

void	Display::render()
{
  SDL_RenderPresent(game->renderer);
}

void		Display::displayTiles(Terrain *terrain)
{
  SDL_Rect	tileset;
  SDL_Rect	win;
  const Tile	*tiles;
  int		size;
  int		tile_width;
  int		i;

  //size of each tile in tileset
  tileset.x = 0;
  tileset.h = 30;
  tileset.w = 30;

  //rect to be blit on window
  win.h = 30;
  win.w = 30;

  tiles = terrain->getTiles();
  size = terrain->getNumberTiles();
  tile_width = TILE_WIDTH;
  i = 0;
  while (i < size)
    {
      tileset.y = tiles[i].type * 30;
      win.x = i % tile_width * 30;
      win.y = i / tile_width * 30;
      SDL_RenderCopy(game->renderer, textures[display::TEXTURE_BASIC_TILESET], &tileset, &win);
      i = i + 1;
    }
}

void		Display::displayObjects(Terrain *terrain)
{
  SDL_Rect		tileset;
  SDL_Rect		win;
  const Object		*objects;
  int			size;
  int			i;

  //size of each tile in tileset
  tileset.x = 0;
  tileset.h = 30;
  tileset.w = 30;

  //rect to be blit on window
  win.h = 30;
  win.w = 30;

  objects = terrain->getObjects();
  size = terrain->getNumberObjects();
  i = 0;
  while (i < size)
    {
      tileset.y = objects[i].type * 30;
      win.x = objects[i].x * 30;
      win.y = objects[i].y * 30;
      SDL_RenderCopy(game->renderer, textures[display::TEXTURE_BASIC_OBJECT_SET], &tileset, &win);
      i = i + 1;
    }
}

void		Display::displayCharacters(Terrain *terrain)
{
  SDL_Rect		tileset;
  SDL_Rect		win;
  const Character	*characters;
  int			size;
  int			i;

  //size of each tile in tileset
  tileset.x = 0;
  tileset.h = 30;
  tileset.w = 30;

  //rect to be blit on window
  win.h = 30;
  win.w = 30;

  characters = terrain->getCharacters();
  size = terrain->getNumberCharacters();
  i = 0;
  while (i < size)
    {
      tileset.y = characters[i].type * 30;
      win.x = characters[i].x - 15;
      win.y = characters[i].y - 15;
      SDL_RenderCopy(game->renderer, textures[display::TEXTURE_BASIC_CHARACTER_SET], &tileset, &win);
      i = i + 1;
    }
}
