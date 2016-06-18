#include "top_header.hpp"
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "camera.hpp"
#include "renderable.hpp"

Display::Display(Game *game) : game(game), renderables()
{
  int i;

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
          std::cerr << "Failed to open a texture: (%s)\n"
                    << SDL_GetError() << std::endl;
	  exit(-1);
	}
      i = i + 1;
    }
}

Display::~Display(void)
{
  int i;

  i = 0;
  while (i < display::TEXTURE_MAX)
    {
      SDL_DestroyTexture(textures[i]);
      i = i + 1;
    }
}

void Display::clearScreen(int r, int g, int b)
{
  SDL_SetRenderDrawColor(game->getRenderer(), r, g, b, 255);
  SDL_RenderClear(game->getRenderer());
}

void Display::displayRenderable(Renderable *renderable)
{
  SDL_Rect      rect;
  Vect<2u, double> tmp;

  rect.w = (*renderable->dimensions)[0] * 60;
  rect.h = (*renderable->dimensions)[1] * 60;
  tmp = (*renderable->position);
  std::cout << "perso at : " << tmp[0] << ", " << tmp[1] << std::endl;
  tmp = (tmp  - getCamera());
  tmp = tmp + Vect<2u, double>(-tmp[1], tmp[0]);
  tmp = tmp  * Vect<2u, double>(60, 30);
  rect.x = tmp[0] + (game->getWindowWidth() - rect.w) / 2;
  rect.y = tmp[1] + game->getWindowHeight() / 2 - rect.h;
  std::cout << "drawng at : " << rect.x << ", " << rect.y << std::endl;
  SDL_RenderCopy(game->getRenderer(), renderable->texture, renderable->srcRect, &rect);
}

void Display::render(void)
{
  unsigned int	i;

  i = 0;
  while (i < renderables.size())
    {
      displayRenderable(renderables[i]);
      i = i + 1;
    }
  SDL_RenderPresent(game->getRenderer());
}

void Display::tileScale(SDL_Rect& win) const
{
  win.x *= 60;
  win.y *= 30;
}

void Display::moveCamera(double x, double y)
{
  camera.moveCamera(x, y);
}

Vect <2, double> const &Display::getCamera() const
{
  return (camera.getCamera());
}

Vect <2, double> const Display::getIngameCursor() const
{
  Vect <2, double>	cursor;
  double		tmp;
  int			x;
  int			y;

  SDL_GetMouseState(&x, &y);
  //vector cursor/camera
  cursor[0] = x - game->getWindowWidth() / 2;
  cursor[1] = y - game->getWindowHeight() / 2;
  //scale;
  cursor[0] /= 120;
  cursor[1] /= 60;
  //deiso
  tmp =  cursor[0];
  cursor[0] += cursor[1];
  cursor[1] -= tmp;

  // Absolute position
  cursor[0] += getCamera()[0];
  cursor[1] += getCamera()[1];
  return (cursor);
}

void Display::isometrize(SDL_Rect& win) const
{
  int tmp;

  tmp = win.x;
  win.x -= win.y;
  win.y += tmp;
}

void Display::fixBoard(SDL_Rect& win) const
{
  Vect <2, double> cam;
  int x;
  int y;

  cam = camera.getCamera();
  x = cam[0] - TILE_WIDTH / 2;
  y = cam[1] - TILE_HEIGHT / 2;
  win.x -= (x - y);
  win.y -= (y + x);
}

void Display::centerBoard(SDL_Rect& win) const
{
  int windowWidth = game->getWindowWidth();
  int windowHeight = game->getWindowHeight();

  win.x += (windowWidth / 2) + (TILE_HEIGHT - TILE_WIDTH) / 2 * 60 - 60;
  if (TILE_HEIGHT > TILE_WIDTH)
    win.y += windowHeight / 2 - TILE_HEIGHT * 30 / 2;
  else if (TILE_HEIGHT < TILE_WIDTH)
    win.y += windowHeight / 2 - TILE_WIDTH * 30 / 2;
  else
    win.y += windowHeight / 2 - TILE_WIDTH * 60 / 2;
}

void Display::smoothScrolling(SDL_Rect& win) const
{
  Vect <2, double> cam;
  Vect <2, double> rest;
  double tmp;

  cam = camera.getCamera();
  rest[0] = cam[0] - (int)cam[0];
  rest[1] = cam[1] - (int)cam[1];
  //isometrize
  tmp = rest[0];
  rest[0] -= rest[1];
  rest[1] += tmp;
  //scale
  rest[0] *= 60;
  rest[1] *= 30;
  //translate
  win.x -= rest[0];
  win.y -= rest[1];
}

void Display::affTile(SDL_Rect const &win, Tile const &tile)
{
  SDL_Rect tileset;

  tileset.x = 0;
  tileset.y = tile.type * 60;
  tileset.w = 120;
  tileset.h = 60;
  SDL_RenderCopy(game->getRenderer(),
                 textures[display::TEXTURE_TILE_GRASS],
                 &tileset, &win);
}

void Display::transformation(Tile const &tile)
{
  SDL_Rect win;

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

void Display::displayLine(Terrain *terrain, SDL_Rect const &rect)
{
  int tmp;
  int x;
  int y;

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

void Display::displayTiles(Terrain *terrain)
{
  Vect <2, double> cam;
  SDL_Rect rect;

  cam = camera.getCamera();
  rect.x = cam[0] - TILE_WIDTH / 2;
  rect.y = cam[1] - TILE_HEIGHT / 2;
  rect.w = rect.x + TILE_WIDTH;
  rect.h = rect.y + TILE_HEIGHT;
  displayLine(terrain, rect);
}

void Display::addRenderable(Renderable *renderable)
{
  renderables.push_back(renderable);
}

void Display::removeRenderable(Renderable *renderable)
{
  unsigned int i;
  
  i = 0;
  while (renderables[i] != renderable)
    {
      i = i + 1;
    }
  renderables.erase(renderables.begin() + i);
}
