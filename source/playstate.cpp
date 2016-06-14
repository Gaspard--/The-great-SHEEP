#include "top_header.hpp"
#include "game.hpp"
#include "playstate.hpp"

//
// Constructor/Destructor
//

void	PlayState::init(Game *mGame)
{
  game = mGame;
  display = new Display(game);
  terrain = new Terrain();
}

void	PlayState::destroy()
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
    }
}

void	PlayState::update()
{
  // Do nothing
}

void	PlayState::draw()
{
  display->clearScreen(0, 0, 0);
  display->displayTiles(terrain);
  display->displayObjects(terrain);

  //random disposition of characters
  terrain->disposeCharacters();
  display->displayCharacters(terrain);
  display->render();
  SDL_Delay(500);
}

void	PlayState::pause()
{
  // Do nothing
}

void	PlayState::resume()
{
  // Do nothing
}
