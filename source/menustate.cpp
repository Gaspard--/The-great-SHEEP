#include "top_header.hpp"
#include "game.hpp"
#include "menustate.hpp"
#include "playstate.hpp"

//
// Constructor/Destructor
//

MenuState::MenuState(Game *game) : game(game)
{
  startButton = IMG_LoadTexture(game->renderer, "assets/startButton.png");
  if (!startButton)
    {
      std::cerr << "Failed to load image : " << SDL_GetError() << std::endl;
      exit(-1);
    }
}

MenuState::~MenuState()
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

  SDL_QueryTexture(startButton, NULL, NULL, &w, &h);
  rect.x = (WINDOW_WIDTH - w) / 2;
  rect.y = (WINDOW_HEIGHT - h) / 2;
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
	  game->changeState(new PlayState(game));
	}
    }
}

void	MenuState::update()
{
  SDL_Rect	start;
  int		w;
  int		h;

  SDL_QueryTexture(startButton, NULL, NULL, &w, &h);
  start.x = (WINDOW_WIDTH - w) / 2;
  start.y = (WINDOW_HEIGHT - h) / 2;
  start.w = w;
  start.h = h;
  SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
  SDL_RenderClear(game->renderer);
  SDL_RenderCopy(game->renderer, startButton, NULL, &start);
}

void	MenuState::draw()
{
  SDL_RenderPresent(game->renderer);
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
