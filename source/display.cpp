#include "top_header.hpp"
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "camera.hpp"
#include "renderable.hpp"

Display::Display(Game *game) : game(game), renderables(),
			       textures{
  Texture(game, "grass_01.png"),
    Texture(game, "grass_02.png"),
    Texture(game, "dry_01.png"),
    Texture(game, "dry_02.png"),
    Texture(game, "water_01.png")
    }
{
}

Display::~Display(void)
{
}

void Display::clearScreen(int r, int g, int b)
{
  SDL_SetRenderDrawColor(game->getRenderer(), static_cast<Uint8>(r), static_cast<Uint8>(g),
			 static_cast<Uint8>(b), Uint8(255));
  SDL_RenderClear(game->getRenderer());
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

void Display::displayRenderable(Renderable *renderable)
{
  SDL_Rect      rect;
  Vect<2u, double> tmp;

  rect.w = static_cast<int>((*renderable->dimensions)[0] * 60.0);
  rect.h = static_cast<int>((*renderable->dimensions)[1] * 60.0);
  tmp = (*renderable->position - getCamera());
  tmp = display::fullIsometrize(tmp);
  rect.x = static_cast<int>(tmp[0]) + ((game->getWindowWidth() - rect.w) / 2);
  rect.y = static_cast<int>(tmp[1]) + game->getWindowHeight() / 2 - rect.h;
  SDL_RenderCopy(game->getRenderer(), renderable->texture->getTexture(), renderable->srcRect, &rect);
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

void Display::moveCamera(double x, double y)
{
  camera.moveCamera(x, y);
}

void Display::setCamera(double x, double y)
{
  camera.setCamera(x, y);
}

Vect <2, double> const &Display::getCamera() const
{
  return (camera.getCamera());
}

Vect<2u, double> const Display::getIngameCursor() const
{
  Vect<2, double>	cursor;
  double		tmp;
  int			x;
  int			y;

  SDL_GetMouseState(&x, &y);
  cursor[0] = x - game->getWindowWidth() / 2;
  cursor[1] = y - game->getWindowHeight() / 2;
  cursor = cursor * Vect<2, double>(1.0 / 120.0, 1.0 / 60.0);
  tmp = cursor[0];
  cursor[0] += cursor[1];
  cursor[1] -= tmp;
  return (cursor + getCamera());
}

void Display::displayTile(SDL_Rect const &win, Tile const &tile)
{
  SDL_Rect tileset;

  tileset.x = 0;
  tileset.y = 0;
  tileset.w = 120;
  tileset.h = 60;
  SDL_RenderCopy(game->getRenderer(),
                 textures[tile.id].getTexture(),
                 &tileset, &win);
}

void Display::smoothScrolling(SDL_Rect& win) const
{
  Vect <2, double> rest;

  rest = display::fullIsometrize(camera.getCamera() - Vect<2u, double>(camera.getFlooredCamera()));
  win.x -= (int)rest[0];
  win.y -= (int)rest[1];
}

void Display::centerBoard(SDL_Rect& win) const
{
  win.x += game->getWindowWidth() / 2 - 60;
  win.y += game->getWindowHeight() / 2 - TILE_DIM * 30;

}

void Display::tileScale(SDL_Rect& win) const
{
  win.x *= 60;
  win.y *= 30;
}

void Display::fixBoard(SDL_Rect& win) const
{
  Vect<2u, int> pos;

  pos = camera.getFlooredCamera() - Vect<2u, int>(TILE_DIM / 2, TILE_DIM / 2);
  win.x -= (pos[0] - pos[1]);
  win.y -= (pos[1] + pos[0]);
}

void Display::isometrize(SDL_Rect& win) const
{
  int tmp;

  tmp = win.x;
  win.x -= win.y;
  win.y += tmp;
}

void Display::transformation(Tile const &tile)
{
  SDL_Rect win;

  win.x = tile.pos[0];
  win.y = tile.pos[1];
  win.w = 120;
  win.h = 60;
  isometrize(win);
  fixBoard(win);
  tileScale(win);
  centerBoard(win);
  smoothScrolling(win);
  displayTile(win, tile);
}

void Display::displayLine2(Terrain &terrain, SDL_Rect const &rect, int x, int y, int line)
{
  while (line > 0)
    {
      if (terrain.isTile(x + rect.x, y + rect.y))
	transformation(terrain.getTile(x + rect.x, y + rect.y));
      ++x;
      --y;
      --line;
    }
}

void Display::displayLine(Terrain &terrain, SDL_Rect const &rect)
{
  int i;
  int x;
  int y;

  i = 0;
  while (i < TILE_DIM - 1)
    {
      x = i - TILE_DIM / 2;
      y = i + TILE_DIM / 2;
      displayLine2(terrain, rect, x, y, TILE_DIM);
      displayLine2(terrain, rect, x + 1, y, TILE_DIM - 1);
      ++i;
    }
  x = i - TILE_DIM / 2;
  y = i + TILE_DIM / 2;
  displayLine2(terrain, rect, x, y, TILE_DIM);
}

void Display::displayTiles(Terrain &terrain)
{
  Vect<2u, int> cam;
  SDL_Rect rect;

  cam = camera.getFlooredCamera();
  rect.x = cam[0] - TILE_DIM / 2;
  rect.y = cam[1] - TILE_DIM / 2;
  rect.w = rect.x + TILE_DIM;
  rect.h = rect.y + TILE_DIM;
  displayLine(terrain, rect);
}
