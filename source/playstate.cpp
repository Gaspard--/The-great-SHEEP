#include "top_header.hpp"
#include "game.hpp"
#include "playstate.hpp"
#include "perso.hpp"

//
// Constructor/Destructor
//

PlayState::PlayState(Game *game) : game(game)
{
  display = new Display(game);
  terrain = new Terrain();
  perso = new Perso(game);
}

PlayState::~PlayState()
{
  delete terrain;
  delete display;
  delete perso;
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
          break;
	case SDL_MOUSEBUTTONDOWN:
	  Vect<2, double> tmp = display->getIngameCursor();
	  printf("click pos: x %f, y %f\n", tmp[0], tmp[1]);
	  perso->moveTo(Vect<2u, double>(event.button.x, event.button.y));
	  break;
	}
      if (event.type != SDL_KEYDOWN)
	return;
      switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          game->quit();
          break;
        case SDLK_UP:
          display->moveCamera(-0.2, -0.2);
          break;
        case SDLK_DOWN:
          display->moveCamera(0.2, 0.2);
          break;
        case SDLK_LEFT:
          display->moveCamera(-0.12, 0.12);
          break;
        case SDLK_RIGHT:
          display->moveCamera(0.12, -0.12);
          break;
	case SDLK_p:
	  Vect<2, double> tmp = display->getCamera();
	  printf("cam pos: x %f, y %f\n", tmp[0], tmp[1]);
	  break;
        }
    }
}

void PlayState::update(void)
{
  // Display tiles
  display->clearScreen(0, 0, 0);
  display->displayTiles(terrain);

  // Display perso
  perso->update();
  this->renderPerso();
}

void PlayState::draw(void)
{
  SDL_RenderPresent(game->getRenderer());
}

void PlayState::pause(void)
{
  // Do nothing
}

void PlayState::resume(void)
{
  // Do nothing
}

void	PlayState::renderPerso()
{
  SDL_Rect	rect;

  rect.w = (*perso->getRenderable().back().dimensions)[0];
  rect.h = (*perso->getRenderable().back().dimensions)[1];
  rect.x = perso->getPosition()[0] - rect.w / 2;
  rect.y = perso->getPosition()[1] - rect.h;
  SDL_RenderCopy(game->getRenderer(), perso->getRenderable()[0].texture, NULL, &rect);
}
