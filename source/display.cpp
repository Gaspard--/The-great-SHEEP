#include "top_header.hpp"
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "camera.hpp"

Display::Display(Game *cGame)
{
  int		i;

  game = cGame;

  // Load textures
  textures[display::TEXTURE_TILE_GRASS] =
    IMG_LoadTexture(game->getRenderer(), "assets/tile_grass.png");
  textures[display::TEXTURE_TILE_WATER] =
    IMG_LoadTexture(game->getRenderer(), "assets/tile_water.png");

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
  SDL_SetRenderDrawColor(game->getRenderer(), r, g, b, 255);
  SDL_RenderClear(game->getRenderer());
}

void	Display::render()
{
  SDL_RenderPresent(game->getRenderer());
}

void	Display::tileScale(SDL_Rect& win)
{
  win.x *= 60;
  win.y *= 30;
}

void	Display::moveCamera(double x, double y)
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

void	Display::fixBoard(SDL_Rect& win)
{
  Vect <2, double> cam;
  int	x;
  int	y;

  cam = camera.getCamera();
  x = cam.data[0] - TILE_WIDTH / 2;
  y = cam.data[1] - TILE_HEIGHT / 2;
  win.x -= (x - y);
  win.y -= (y + x);
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

void			Display::smoothScrolling(SDL_Rect& win)
{
  Vect <2, double>	cam;
  Vect <2, double>	rest;
  double		tmp;

  cam = camera.getCamera();
  rest.data[0] = cam.data[0] - (int)cam.data[0];
  rest.data[1] = cam.data[1] - (int)cam.data[1];
  //isometrize
  tmp = rest.data[0];
  rest.data[0] -= rest.data[1];
  rest.data[1] += tmp;
  //scale
  rest.data[0] *= 60;
  rest.data[1] *= 30;
  //translate
  win.x -= rest.data[0];
  win.y -= rest.data[1];
}

void		Display::affTile(const SDL_Rect& win, const Tile &tile)
{
  SDL_Rect	tileset;

  tileset.x = 0;
  tileset.y = tile.type * 60;
  tileset.w = 120;
  tileset.h = 60;
  SDL_RenderCopy(game->getRenderer(), textures[display::TEXTURE_TILE_GRASS], &tileset, &win);
}

void		Display::transformation(const Tile& tile)
{
  SDL_Rect	win;

  win.x = tile.x;
  win.y = tile.y;
  win.w = 120;
  win.h = 60;
  isometrize(win);
  fixBoard(win);
  tileScale(win);
  centerBoard(win);
  smoothScrolling(win);
  affTile(win, tile);
}

void	Display::displayLine(Terrain *terrain, const SDL_Rect& rect)
{
  int	tmp;
  int	x;
  int	y;

  tmp = rect.x;
  y = rect.y;
  while (y < rect.h)
    {
      x = tmp;
      while (x < rect.w)
	{
	  if (terrain->isTile(x ,y))
	    transformation(terrain->getTile(x, y));
	  ++x;
	}
      ++y;
    }
}

void			Display::displayTiles(Terrain *terrain)
{
  Vect <2, double>	cam;
  SDL_Rect		rect;

  cam = camera.getCamera();
  rect.x = cam.data[0] - TILE_WIDTH / 2;
  rect.y = cam.data[1] - TILE_HEIGHT / 2;
  rect.w = rect.x + TILE_WIDTH;
  rect.h = rect.y + TILE_HEIGHT;
  displayLine(terrain, rect);
}
