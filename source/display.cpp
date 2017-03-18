#include "top_header.hpp"
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "camera.hpp"
#include "renderable.hpp"
#include "playstate.hpp"

Display::Display(Game &game, PlayState &playState)
  : game(game),  playState(playState),
    tileset(game, "basic_ground_tiles.png"),  renderables()
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
  std::sort(renderables.begin(), renderables.end(), [this](Followable<Renderable> &A, Followable<Renderable> &B) {
      return (camera.fullIsometrize(A->position)[1] < camera.fullIsometrize(B->position)[1]);
    });
  std::for_each(renderables.begin(), renderables.end(), [this](Followable<Renderable> &r) {
      this->displayRenderable(*r);
    });
}

void Display::displayRenderable(Renderable const &renderable)
{
  Vect<2u, double> const tmp(camera.fullIsometrize(renderable.position));
  Vect<2u, int> const wh((renderable.dimensions * 120.0));
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
  Vect<2, int>		cursorPos(0u, 0u);
  int			h(maxRenderHeight);

  SDL_GetMouseState(&cursorPos[0], &cursorPos[1]);
  Vect<2, double>	trueCursor(camera.fullDesisometrize(cursorPos - Vect<2u, int>{game.getWindowWidth() / 2, game.getWindowHeight() / 2}));

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

void Display::displayTile(Tile const & tile)
{
  constexpr Vect<2u, int> wh(1024 / 8, 896 / 7);
  SDL_Rect rect = {
    .x = (tile.id % 8) * wh[0],
    .y = ((tile.id) / 8) * wh[1],
    .w = wh[0],
    .h = wh[1],
  };
  Vect<2u, double> tmp((camera.fullIsometrize(tile.pos))
		       + Vect<2u, double>(game.getWindowWidth() / 2u - 60u,
			  game.getWindowHeight() / 2u - 30u - tile.height * 15u));
  SDL_Rect win = {
    .x = tmp[0],
    .y = tmp[1],
    .w = 120,
    .h = 120
  };
  maxRenderHeight = std::max(tile.height, maxRenderHeight);
  SDL_RenderCopy(game.getRenderer(), tileset.getTexture(), &rect, &win);
}

void Display::displayLine(Terrain &terrain, Vect<2, int> pos, bool cut)
{
  for (size_t line(TILE_DIM - cut); line; --line)
    {
      displayTile(terrain.getTile(pos[0] + cut, pos[1]));
      pos += {1, -1};
    }
}

void Display::displayTiles(Terrain &terrain)
{
  Vect<2u, int> const cam(camera.getFlooredCamera());
  Vect<2u, int> pos(cam[0] - TILE_DIM + 1, cam[1]);
  maxRenderHeight = 0;

  for (size_t i(0); i < TILE_DIM - 1; ++i)
    {
      displayLine(terrain, pos, 0);
      displayLine(terrain, pos, 1);
      pos += {1, 1};
    }
  displayLine(terrain, pos, 0);
}
