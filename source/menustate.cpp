#include <iostream>
#include "top_header.hpp"
#include "game.hpp"
#include "menustate.hpp"
#include "playstate.hpp"

//
// Constructor/Destructor
//

MenuState::MenuState(Game *game) : GameState(game), startButton(game, "startButton.png")
{
}

MenuState::~MenuState()
{
}

//
// Game flow methods
//
void MenuState::handleEvent(void)
{
  SDL_Event		event;
  SDL_Rect		rect;
  SDL_MouseButtonEvent	mouse;
  int			w;
  int			h;

  SDL_QueryTexture(startButton.getTexture(), NULL, NULL, &w, &h);
  rect.x = (game->getWindowWidth() - w) / 2;
  rect.y = (game->getWindowHeight() - h) / 2;
  rect.w = w;
  rect.h = h;
  if (SDL_PollEvent(&event) != 0)
    {
      if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
				     event.key.keysym.sym == SDLK_ESCAPE))
	game->quit();
      mouse = event.button;
      if (mouse.button == SDL_BUTTON_LEFT &&
	  mouse.x >= rect.x && mouse.x < rect.x + rect.w &&
	  mouse.y >= rect.y && mouse.y < rect.y + rect.h)
	{
	  game->changeState(new PlayState(game));
	}
    }
}

void MenuState::update(void)
{
  SDL_Rect	start;
  int		w;
  int		h;

  SDL_QueryTexture(startButton.getTexture(), NULL, NULL, &w, &h);
  start.x = (game->getWindowWidth() - w) / 2;
  start.y = (game->getWindowHeight() - h) / 2;
  start.w = w;
  start.h = h;
  SDL_SetRenderDrawColor(game->getRenderer(), 255, 255, 255, 255);
  SDL_RenderClear(game->getRenderer());
  SDL_RenderCopy(game->getRenderer(), startButton.getTexture(), NULL, &start);
}

void	MenuState::draw()
{
  SDL_RenderPresent(game->getRenderer());
}

void MenuState::pause(void)
{
  // Do nothing
}

void MenuState::resume(void)
{
  // Do nothing
}
