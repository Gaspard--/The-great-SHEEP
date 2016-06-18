#include "top_header.hpp"
#include "game.hpp"
#include "playstate.hpp"
#include "logic.hpp"
#include "entity_handler.hpp"

//
// Constructor/Destructor
//

void PlayState::init(Game *game)
{
  this->game = game;
  display = new Display(game);
  terrain = new Terrain();
  logic = new Logic();
  entityHandler = new EntityHandler(this);
}

void PlayState::destroy(void)
{
  delete terrain;
  delete display;
  delete logic;
  delete entityHandler;
}

//
// Game flow methods
//
void PlayState::handleEvent(void)
{
  SDL_Event event;

  if (SDL_PollEvent(&event) != 0)
    {
      switch (event.type)
        {
        case SDL_QUIT:
          game->quit();
	  return ;
	}
      switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          game->quit();
          return ;
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

Logic *PlayState::getLogic()
{
  return (logic);
}

Terrain *PlayState::getTerrain()
{
  return (terrain);
}

EntityHandler *PlayState::getEntityHandler()
{
  return (entityHandler);
}
