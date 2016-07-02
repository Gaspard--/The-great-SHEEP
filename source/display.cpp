#include "top_header.hpp"
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "camera.hpp"
#include "renderable.hpp"
#include "playstate.hpp"
#include "renderable_compare.hpp"

Display::Display(Game *game, PlayState *playState) : game(game),  playState(playState), renderables(),
						     tileset(game, "basic_ground_tiles.png")
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

    std::sort(renderables.begin(), renderables.end(), RenderableCompare(this));
    while (i < renderables.size())
      {
	displayRenderable(renderables[i]);
	i = i + 1;
      }
  }
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
  tmp = *renderable->position - getCameraPosition();
  tmp = fullIsometrize(tmp);
  rect.x = static_cast<int>(tmp[0]) + ((game->getWindowWidth() - rect.w) / 2);
  rect.y = static_cast<int>(tmp[1]) + game->getWindowHeight() / 2 - rect.h;
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

Vect <2, double> Display::getCameraPosition() const
{
  return (camera.getPosition());
}

void Display::moveCamera(Vect<2, double> offset)
{
  camera.move(offset);
}

void Display::setCameraPosition(Vect<2, double> newPosition)
{
  camera.setPosition(newPosition);
}

Vect <2, int> Display::getCameraAngle() const
{
  return (camera.getAngle());
}

void Display::setCameraAngle(Vect<2, int> angle)
{
  camera.setAngle(angle);
}

Vect<2u, double> Display::getIngameCursor() const
{
  Vect<2, double>	true_cursor;
  int			x;
  int			y;
  int			h;

  SDL_GetMouseState(&x, &y);
  true_cursor[0] = x - game->getWindowWidth() / 2;
  true_cursor[1] = y - game->getWindowHeight() / 2;
  true_cursor = true_cursor * Vect<2u, double>(1.0 / 120.0, 1.0 / 60.0);
  true_cursor = true_cursor + Vect<2u, double>(true_cursor[1], -true_cursor[0]) + getCameraPosition();
  h = maxRenderHeight;
  while (h > 0)
    {
      Vect<2, double> cursor(true_cursor + Vect<2u, double>(1.0, 1.0) * h * 0.25);

      x = static_cast<int>(round(cursor[0]));
      y = static_cast<int>(round(cursor[1]));
      if (playState->getTerrain().getTile(x, y).height >= h)
	return (cursor);
      h = h - 1;
    }
  return (true_cursor);
}

void Display::centerBoard(Vect<2, int>& pos) const
{
  Vect<2u, int> angle(camera.getAngle());

  angle[0] ?
    pos[0] += game->getWindowWidth() / 2 + 30:
    pos[0] += game->getWindowWidth() / 2 - 60;

  angle[0] ?
    pos[1] += game->getWindowHeight() / 2 - 60 :
    pos[1] += game->getWindowHeight() / 2 - 30;
}

void Display::calcAngle(Vect<2, int>& pos)
{
  Vect<2u, int> angle(camera.getAngle());

  if (angle[0])
    {
      int tmp(pos[0]);

      pos[0] = game->getWindowWidth() / 2 + (pos[1] - game->getWindowHeight() / 2);
      pos[1] = game->getWindowHeight() / 2 + (game->getWindowWidth() / 2 - tmp);
    }
}

void Display::displayTile(SDL_Rect const & win, Tile const & tile)
{
  SDL_Rect rect;

  rect.w = 1024 / 8;
  rect.h = 896 / 7;
  rect.x = (tile.id % 8) * rect.w;
  rect.y = ((tile.id) / 8) * rect.h;
  SDL_RenderCopy(game->getRenderer(),
                 tileset.getTexture(),
                 &rect, &win);
}

void Display::transformation(Tile const & tile)
{
  SDL_Rect win;
  Vect<2u, int> angle(camera.getAngle());
  Vect<2u, int> tmp(tile.pos);

  angle[0] ?
    tmp = fullIsometrizeRev(tmp) - Vect<2u, int>(fullIsometrizeRev(getCameraPosition())) :
    tmp = fullIsometrize(tmp) - Vect<2u, int>(fullIsometrize(getCameraPosition()));

  centerBoard(tmp);
  calcAngle(tmp);

  win.x = tmp[0];
  win.y = tmp[1] - tile.height * 15;
  win.w = 120;
  win.h = 120;

  maxRenderHeight = std::max(tile.height, maxRenderHeight);

  displayTile(win, tile);
}

void Display::displayLine(Terrain& terrain, SDL_Rect const & rect, int x, int y)
{
  Vect<2u, int> angle(camera.getAngle());
  int line(TILE_DIM);

  while (line > 0)
    {
      transformation(terrain.getTile(x + rect.x , y + rect.y));
      angle[0] ? ++y : --y;
      ++x;
      --line;
    }
}

void Display::displayLines(Terrain& terrain, SDL_Rect const & rect)
{
  Vect<2u, int> angle(camera.getAngle());
  int x(-(TILE_DIM / 2));
  int y(angle[0] ? -(TILE_DIM / 2) : (TILE_DIM / 2));
  int decalage(angle[0] ? -1 : 1);
  int i(0);

  while (i < TILE_DIM - 1)
    {
      displayLine(terrain, rect, x, y);
      displayLine(terrain, rect, x + decalage, y);
      angle[0] ? --x : ++x;
      ++y;
      ++i;
    }
  displayLine(terrain, rect, x, y);
}

void Display::getStartRect(SDL_Rect& rect)
{
  Vect<2u, int> angle(camera.getAngle());
  Vect<2u, int> cam(camera.getFlooredCamera());

  angle[0] ?
    rect.x = cam[0] + TILE_DIM / 2 :
    rect.x = cam[0] - TILE_DIM / 2;
  rect.y = cam[1] - TILE_DIM / 2;
}

void Display::displayTiles(Terrain& terrain)
{
  SDL_Rect rect;

  maxRenderHeight = 0;
  getStartRect(rect);
  rect.w = rect.x + TILE_DIM;
  rect.h = rect.y + TILE_DIM;
  displayLines(terrain, rect);
}
