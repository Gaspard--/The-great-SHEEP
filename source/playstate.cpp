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
  perso = new Perso(game, this, Vect<2, double>(10, 14));
  perso2 = new Perso(game, this, Vect<2, double>(14, 10));
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
          display.setCameraPosition(perso->getPosition());
	  break;
	case SDLK_F3:
	  game->toggleShowFps();
	  break;
        case SDLK_UP:
          display.moveCamera(Vect<2, double>(0, -0.2));
          break;
        case SDLK_DOWN:
          display.moveCamera(Vect<2, double>(0, 0.2));
          break;
        case SDLK_LEFT:
          display.moveCamera(Vect<2, double>(-0.2, 0));
          break;
        case SDLK_RIGHT:
          display.moveCamera(Vect<2, double>(0.2, 0));
          break;
        case SDLK_a:
	  // change south, east
          display.setCameraAngle(Vect<2, int>(1, 0));
          break;
        case SDLK_q:
	  // change top, down
          display.setCameraAngle(Vect<2, int>(0, 1));
          break;
	case SDLK_p:
	  {
	    Vect<2, double> tmp = display.getCameraPosition();
            // TODO: Use `cout`
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
  display.render();
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
