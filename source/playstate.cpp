#include "top_header.hpp"
#include "game.hpp"
#include "playstate.hpp"

//
// Constructor/Destructor
//

void PlayState::init(Game *mGame)
{
  game = mGame;
  display = new Display(game);
  terrain = new Terrain();
}

void PlayState::destroy(void)
{
  delete terrain;
  delete display;
}

//
// Game flow methods
//
void PlayState::handleEvent(void)
{
  SDL_Event event;

  if (SDL_PollEvent(&event) != 0)
    {
      switch (event.key.keysym.sym)
        {
        case SDL_QUIT:
          game->quit();
          break;
	}
      switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          game->quit();
          break;
        case SDLK_UP:
          display->moveCamera(0, -0.2);
          break;
        case SDLK_DOWN:
          display->moveCamera(0, 0.2);
          break;
        case SDLK_LEFT:
          display->moveCamera(-0.2, 0);
          break;
        case SDLK_RIGHT:
          display->moveCamera(0.2, 0);
          break;
        }
    }
}

void PlayState::update(void)
{
  // Do nothing
}

void PlayState::draw(void)
{
  display->clearScreen(0, 0, 0);
  display->displayTiles(terrain);
  display->render();
}

void PlayState::pause(void)
{
  // Do nothing
}

void PlayState::resume(void)
{
  // Do nothing
}
