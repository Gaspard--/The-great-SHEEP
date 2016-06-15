#include "top_header.hpp"
#include "game.hpp"
#include "playstate.hpp"

//
// Constructor/Destructor
//

PlayState::PlayState(Game *game) : game(game)
{
  display = new Display(game);
  terrain = new Terrain();
}

PlayState::~PlayState()
{
  delete terrain;
  delete display;
}

//
// Game flow methods
//
void	PlayState::handleEvent()
{
  SDL_Event		event;

  if (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
	{
	  game->quit();
	}
      else if (event.key.keysym.sym == SDLK_UP)
      	display->moveCamera(0, -10);
      else if (event.key.keysym.sym == SDLK_DOWN)
      	display->moveCamera(0, 10);
      else if (event.key.keysym.sym == SDLK_LEFT)
      	display->moveCamera(-10, 0);
      else if (event.key.keysym.sym == SDLK_RIGHT)
      	display->moveCamera(10, 0);
    }
}

void	PlayState::update()
{
  display->clearScreen(0, 0, 0);
  display->displayTiles(terrain);
}

void	PlayState::draw()
{
  SDL_RenderPresent(game->renderer);
}

void	PlayState::pause()
{
  // Do nothing
}

void	PlayState::resume()
{
  // Do nothing
}
