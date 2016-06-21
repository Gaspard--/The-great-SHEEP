#include "top_header.hpp"
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "camera.hpp"
#include "renderable.hpp"
#include "playstate.hpp"

Display::Display(Game *game, PlayState *playState) : game(game),  playState(playState), renderables(),
						     tileset(game, "basic_ground_tiles.png"), textures
{
  Texture(game, "grass_01.png"),
    Texture(game, "grass_02.png"),
    Texture(game, "dry_01.png"),
    Texture(game, "dry_02.png"),
    Texture(game, "water_01.png"),
}
{
}

Display::~Display()
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
  clearScreen(0, 0, 0);
  displayTiles(playState->getTerrain());
  {
    unsigned int	i(0);

    while (i < renderables.size())
      {
	displayRenderable(renderables[i]);
	i = i + 1;
      }
  }
  SDL_RenderPresent(game->getRenderer());
}

void Display::displayRenderable(Renderable *renderable)
{
  SDL_Rect      rect;
  Vect<2u, double> tmp;
  int x;
  int y;

  rect.w = static_cast<int>((*renderable->dimensions)[0] * 120.0);
  rect.h = static_cast<int>((*renderable->dimensions)[1] * 120.0);
  x = (int)round((*renderable->position)[0]);
  y = (int)round((*renderable->position)[1]);
  tmp = (*renderable->position - getCamera());
  tmp = display::fullIsometrize(tmp);
  rect.x = static_cast<int>(tmp[0]) + ((game->getWindowWidth() - rect.w) / 2);
  rect.y = static_cast<int>(tmp[1]) + game->getWindowHeight() / 2 - rect.h;
  if (playState->getTerrain().isTile(x, y))
    rect.y -= playState->getTerrain().getTile(x, y).height * 15;
  SDL_RenderCopy(game->getRenderer(), renderable->texture->getTexture(), renderable->srcRect, &rect);
}

void Display::addRenderable(Renderable *renderable)
{
  renderables.push_back(renderable);
}

void Display::removeRenderable(Renderable *renderable)
{
  unsigned int i(0);

  while (renderables[i] != renderable)
    i = i + 1;
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
  Vect<2, double>	true_cursor;
  int			x;
  int			y;
  int			h;

  SDL_GetMouseState(&x, &y);
  true_cursor[0] = x - game->getWindowWidth() / 2;
  true_cursor[1] = y - game->getWindowHeight() / 2;
  true_cursor = true_cursor * Vect<2u, double>(1.0 / 120.0, 1.0 / 60.0);
  true_cursor = true_cursor + Vect<2u, double>(true_cursor[1], -true_cursor[0]) + getCamera();
  h = 10;
  while (h > 0)
    {
      Vect<2, double> cursor(true_cursor + Vect<2u, double>(1.0, 1.0) * h * 0.25);
      std::cout << "trying h = " << h << std::endl;
  
      x = static_cast<int>(round(cursor[0]));
      y = static_cast<int>(round(cursor[1]));
      if ((playState->getTerrain().isTile(x, y) ? playState->getTerrain().getTile(x, y).height : 0) >= h)
	return (cursor);
      h = h - 1;
    }
  return (true_cursor);
}

void Display::displayTile(SDL_Rect const &win, Tile const &tile)
{
  SDL_Rect rect;

  rect.w = 1024 / 8 ;
  rect.h = 896 / 7;
  rect.x = (tile.id % 8) * rect.w;
  rect.y = ((tile.id) / 8) * rect.h;
  SDL_RenderCopy(game->getRenderer(),
                 tileset.getTexture(),
                 &rect, &win);
}

void Display::centerBoard(SDL_Rect& win) const
{
  win.x += game->getWindowWidth() / 2 - 60;
  win.y += game->getWindowHeight() / 2 - 30;
}

void Display::transformation(Tile const &tile)
{
  SDL_Rect win;
  Vect<2u, int> tmp(tile.pos);

  tmp = display::fullIsometrize(tmp) - Vect<2u, int>(display::fullIsometrize(camera.getCamera()));
  win.x = tmp[0];
  win.y = tmp[1] - tile.height * 15;
  win.w = 120;
  win.h = 120;
  centerBoard(win);
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
