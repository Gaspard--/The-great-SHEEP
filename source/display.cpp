#include "top_header.hpp"
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "camera.hpp"
#include "renderable.hpp"
#include "playstate.hpp"

Display::Display(Game &game, PlayState &playState)
  : game(game),  playState(playState), renderables(),
    tileset(game, "basic_ground_tiles.png")
{
}

Display::~Display()
{
}

void Display::clearScreen(int r, int g, int b)
{
  SDL_SetRenderDrawColor(game.getRenderer(), static_cast<Uint8>(r), static_cast<Uint8>(g),
			 static_cast<Uint8>(b), Uint8(255));
  SDL_RenderClear(game.getRenderer());
}

void Display::render(void)
{
  clearScreen(0, 0, 0);
  displayTiles(playState.getTerrain());
  std::sort(renderables.begin(), renderables.end(), [this](Renderable *A, Renderable *B) {
      return (fullIsometrize(A->position)[1] < fullIsometrize(B->position)[1]);
    });
  std::for_each(renderables.begin(), renderables.end(), [this](Renderable *r) {
      this->displayRenderable(*r);
    });
}

void Display::displayRenderable(Renderable const &renderable)
{
  Vect<2u, double> const tmp(fullIsometrize(renderable.position - getCameraPosition()));
  Vect<2u, int> const wh((renderable.dimensions).map([](double a){
	return (a * 120.0);
      }));
  Vect<2u, int> const pos((int)round((renderable.position)[0]),
			  (int)round((renderable.position)[1]));
  SDL_Rect rect = {
    .x = static_cast<int>(tmp[0]) + ((game.getWindowWidth() - wh[0]) / 2),
    .y = static_cast<int>(tmp[1]) + game.getWindowHeight() / 2 - wh[1]
    - playState.getTerrain().getTile(pos[0], pos[1]).height * 15,
    .w = wh[0],
    .h = wh[1],
  };

  SDL_RenderCopy(game.getRenderer(), renderable.texture->getTexture(), renderable.srcRect, &rect);
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

Vect<2u, double> Display::getIngameCursor() const
{
  Vect<2, double>	trueCursor;
  Vect<2, int>		cursorPos;
  int			h(maxRenderHeight);

  SDL_GetMouseState(&cursorPos[0], &cursorPos[1]);
  trueCursor = (cursorPos - Vect<2u, int>{game.getWindowWidth() / 2, game.getWindowHeight() / 2});
  trueCursor *= Vect<2u, double>(1.0 / 120.0, 1.0 / 60.0);
  trueCursor +=  Vect<2u, double>(trueCursor[1], -trueCursor[0]) + getCameraPosition();
  while (h > 0)
    {
      Vect<2, double> cursor(trueCursor + Vect<2u, double>(1.0, 1.0) * h * 0.25);

      cursorPos = {static_cast<int>(round(cursor[0])), static_cast<int>(round(cursor[1]))};
      if (playState.getTerrain().getTile(cursorPos[0], cursorPos[1]).height >= h)
	return (cursor);
      h = h - 1;
    }
  return (trueCursor);
}

void Display::displayTile(SDL_Rect const & win, Tile const & tile)
{
  constexpr Vect<2u, int> wh(1024 / 8, 896 / 7);
  SDL_Rect rect = {
    .x = (tile.id % 8) * wh[0],
    .y = ((tile.id) / 8) * wh[1],
    .w = wh[0],
    .h = wh[1],
  };

  SDL_RenderCopy(game.getRenderer(), tileset.getTexture(), &rect, &win);
}

void Display::transformation(Tile const & tile)
{
  Vect<2u, int> tmp(fullIsometrize(tile.pos)
		    - Vect<2u, int>(fullIsometrize(getCameraPosition()))
		    + Vect<2u, int>(game.getWindowWidth() / 2 - 60,
				    game.getWindowHeight() / 2 - 30 - tile.height * 15));
  SDL_Rect win = {
    .x = tmp[0],
    .y = tmp[1],
    .w = 120,
    .h = 120
  };

  maxRenderHeight = std::max(tile.height, maxRenderHeight);
  displayTile(win, tile);
}

void Display::displayLine(Terrain &terrain, Vect<2u, int> const & rect, Vect<2, int> pos, bool cut)
{
  int line(TILE_DIM - cut);

  while (line > 0)
    {
      transformation(terrain.getTile(pos[0] + rect[0] + cut, pos[1] + rect[1]));
      pos += {1, -1};
      --line;
    }
}

void Display::displayLines(Terrain &terrain, Vect<2u, int> const & rect)
{
  Vect<2u, int> pos(-(TILE_DIM / 2), (TILE_DIM / 2));
  int i(0);

  while (i < TILE_DIM - 1)
    {
      displayLine(terrain, rect, pos, 0);
      displayLine(terrain, rect, pos, 1);
      pos += {1, 1};
      ++i;
    }
  displayLine(terrain, rect, pos, 0);
}

void Display::displayTiles(Terrain &terrain)
{
  Vect<2u, int> const cam(camera.getFlooredCamera());
  Vect<2u ,int> const rect = {
    cam[0] - TILE_DIM / 2 + 1,
    cam[1] - TILE_DIM / 2,
    // .w = cam[0] + TILE_DIM / 2 + 1,
    // .h = cam[1] + TILE_DIM / 2
  };

  maxRenderHeight = 0;
  displayLines(terrain, rect);
}
