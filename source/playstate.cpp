#include "top_header.hpp"
#include "game.hpp"
#include "playstate.hpp"
#include "logic.hpp"
#include "entity_handler.hpp"
#include "perso.hpp"

//
// Constructor/Destructor
//

PlayState::PlayState(Game *game) : GameState(game), display(game, this), entityHandler(this)
{
  perso = new Perso(game, this, Vect<2, double>(2, 4));
  perso2 = new Perso(game, this, Vect<2, double>(8, 10));
}

PlayState::~PlayState()
{
  delete perso;
  delete perso2;
}

//
// Game flow methods
//
void PlayState::handleEvent(void)
{
  SDL_Event event;

  while (SDL_PollEvent(&event) != 0)
    {
      switch (event.type)
        {
        case SDL_QUIT:
          game->quit();
          return;
	case SDL_MOUSEBUTTONDOWN:
	  if (event.button.button == SDL_BUTTON_LEFT)
	    perso->moveTo(display.getIngameCursor());
	  else if (event.button.button == SDL_BUTTON_RIGHT)
	    perso2->moveTo(display.getIngameCursor());
	  break;
	}
      if (event.type != SDL_KEYDOWN)
	return;
      switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          game->quit();
          return;
        case SDLK_SPACE:
	  {
	    Vect<2, double> pos = perso->getPosition();
	    display.setCamera(pos[0], pos[1]);
	  }
	  break;
	case SDLK_F3:
	  game->toggleShowFps();
	  break;
        case SDLK_UP:
          display.moveCamera(0, -0.2);
          break;
        case SDLK_DOWN:
          display.moveCamera(0, 0.2);
          break;
        case SDLK_LEFT:
          display.moveCamera(-0.2, 0);
          break;
        case SDLK_RIGHT:
          display.moveCamera(0.2, 0);
          break;
	case SDLK_p:
	  {
	    Vect<2, double> tmp = display.getCamera();
	    printf("cam pos: x %f, y %f\n", tmp[0], tmp[1]);
	  }
	  break;
        }
    }
}

void PlayState::update(void)
{
  logic.tick();
  // Display perso
  perso->update();
  perso2->update();
}

void PlayState::draw(void)
{
  display.render();
  //  SDL_RenderPresent(game->getRenderer());
}

void PlayState::pause(void)
{
  // Do nothing
}

void PlayState::resume(void)
{
  // Do nothing
}

Logic& PlayState::getLogic()
{
  return (logic);
}

Terrain& PlayState::getTerrain()
{
  return (terrain);
}

EntityHandler& PlayState::getEntityHandler()
{
  return (entityHandler);
}

Display& PlayState::getDisplay()
{
  return (display);
}
