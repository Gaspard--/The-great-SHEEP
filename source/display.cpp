#include "top_header.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "object.hpp"
#include "character.hpp"
#include "camera.hpp"

Display::Display()
{

  if (SDL_Init(SDL_INIT_VIDEO))
    {
      fprintf(stderr, "Failed to initialise SDL : (%s)\n", SDL_GetError());
      exit(-1);
    }

  // Create widnow
  window = SDL_CreateWindow("The great SHEEP.",
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     WINDOW_WIDTH,
			     WINDOW_HEIGHT,
			     SDL_WINDOW_SHOWN);
  if (!window)
    {
      fprintf(stderr,"Failed to open a window : (%s)\n", SDL_GetError());
      exit(-1);
    }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
    {
      fprintf(stderr,"Failed to create renderer : (%s)\n", SDL_GetError());
      exit(-1);
    }

  // Load textures

  textures[display::TEXTURE_BASIC_TILESET] = IMG_LoadTexture(renderer, "assets/basic_tileset.png");
  textures[display::TEXTURE_BASIC_OBJECT_SET] =
    IMG_LoadTexture(renderer, "assets/basic_object_set.png");
  textures[display::TEXTURE_BASIC_CHARACTER_SET] =
    IMG_LoadTexture(renderer, "assets/basic_character_set.png");
  textures[display::TEXTURE_TILE_GRASS] =
    IMG_LoadTexture(renderer, "assets/tile_grass.png");
  textures[display::TEXTURE_TILE_WATER] =
     IMG_LoadTexture(renderer, "assets/tile_water.png");

  int i;

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
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void	Display::clearScreen(int r, int g, int b)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderClear(renderer);
}

void	Display::render()
{
  SDL_RenderPresent(renderer);
}

void	Display::displayTest()
{
}

void	Display::tileScale(SDL_Rect& win)
{
  win.x *= 60;
  win.y *= 30;
}

void	Display::moveCamera(int x, int y)
{
  camera.moveCamera(x, y);
}

void	Display::isometrize(SDL_Rect& win)
{
  int	tmp;

  tmp = win.x;
  win.x -= win.y;
  win.y += tmp;
}

void	Display::fixBoard(SDL_Rect& win, const SDL_Rect& cam)
{
  win.x -= (cam.x - cam.y);
  win.y += (-cam.y - cam.x);
}

void	Display::centerBoard(SDL_Rect& win)
{
  win.x += (WINDOW_WIDTH / 2) + (TILE_HEIGHT - TILE_WIDTH) / 2 * 60 - 60;
  if (TILE_HEIGHT > TILE_WIDTH)
    win.y += WINDOW_HEIGHT / 2 - TILE_HEIGHT * 30 / 2;
  else if (TILE_HEIGHT < TILE_WIDTH)
    win.y += WINDOW_HEIGHT / 2 - TILE_WIDTH * 30 / 2;
  else
    win.y += WINDOW_HEIGHT / 2 - TILE_WIDTH * 60 / 2;
}

void	Display::movementShake(SDL_Rect& win, const SDL_Rect& cam)
{
  win.x += cam.x % 60;
  win.y -= cam.y % 30;
}

void		Display::displayTiles(Terrain *terrain)
{
  Tile		elem;
  SDL_Rect	cam;
  SDL_Rect	cam2;
  SDL_Rect	tileset;
  SDL_Rect	win;
  int		i;
  int		size;
  int	x;
  int	y;

  //size of each tile in tileset
  tileset.x = 0;
  tileset.w = 120;
  tileset.h = 60;

  //rect to be blit on window
  win.w = 120;
  win.h = 60;

  cam = camera.getAbstractCamera();
  cam2 = camera.getWindowCamera();

  size = cam.w * cam.h;

  i = 0;
  while (i < size)
    {
      x = i % cam.w + cam.x;
      y = i / cam.w + cam.y;

      if (terrain->isTile(x ,y))
	{

	  elem = terrain->getTile(x, y);

	  win.x = elem.x;
	  win.y = elem.y;

	  isometrize(win);
	  fixBoard(win, cam);
	  tileScale(win);
	  centerBoard(win);

	  //	  movementShake(win, cam2);

	  tileset.y = elem.type * 60;

	  SDL_RenderCopy(renderer, textures[display::TEXTURE_TILE_GRASS], &tileset, &win);
	}

      i = i + 1;
    }

}
