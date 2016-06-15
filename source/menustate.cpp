#include "top_header.hpp"
#include "game.hpp"
#include "menustate.hpp"
#include "playstate.hpp"

//
// Constructor/Destructor
//

void	MenuState::init(Game *mGame)
{
  game = mGame;
  startButton = IMG_LoadTexture(game->getRenderer(),
                                "assets/startButton.png");
}

void	MenuState::destroy()
{
  SDL_DestroyTexture(startButton);
}

//
// Game flow methods
//
void	MenuState::handleEvent()
{
  SDL_Event		event;
  SDL_Rect		rect;
  SDL_MouseButtonEvent	mouse;
  int			w;
  int			h;

  // Code en dur bien dégueulasse :D
  SDL_QueryTexture(startButton, NULL, NULL, &w, &h);
  rect.x = (game->getWindowWidth() - w) / 2;
  rect.y = (game->getWindowHeight() - h) / 2;
  rect.w = w;
  rect.h = h;
  if (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
	{
	  game->quit();
	}
      mouse = event.button;
      if (mouse.button == SDL_BUTTON_LEFT &&
	  mouse.x >= rect.x && mouse.x < rect.x + rect.w &&
	  mouse.y >= rect.y && mouse.y < rect.y + rect.h)
	{
	  game->changeState(new PlayState());
	}
    }
}

void	MenuState::update()
{
  // Do nothing
}

void	MenuState::draw()
{
  SDL_Rect	start;
  int		w;
  int		h;

  // Code en dur bien dégueulasse :D
  SDL_QueryTexture(startButton, NULL, NULL, &w, &h);
  start.x = (game->getWindowWidth() - w) / 2;
  start.y = (game->getWindowHeight() - h) / 2;
  start.w = w;
  start.h = h;
  SDL_SetRenderDrawColor(game->getRenderer(), 255, 255, 255, 255);
  SDL_RenderClear(game->getRenderer());
  SDL_RenderCopy(game->getRenderer(), startButton, NULL, &start);
  SDL_RenderPresent(game->getRenderer());
  SDL_Delay(20);
}

void	MenuState::pause()
{
  // Do nothing
}

void	MenuState::resume()
{
  // Do nothing
}
