#include "top_header.hpp"
#include "game.hpp"
#include "playstate.hpp"
#include "logic.hpp"
#include "entity_handler.hpp"
#include "perso.hpp"

//
// Constructor/Destructor
//

PlayState::PlayState(Game *game) : game(game)
{
  display = new Display(game);
  terrain = new Terrain();
  logic = new Logic();
  perso = new Perso(game, this, Vect<2, double>(0, 0));
  entityHandler = new EntityHandler(this);
}

PlayState::~PlayState()
{
  delete perso;
  // entities shold all be deleted at this point
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
          return;
	case SDL_MOUSEBUTTONDOWN:
	  perso->moveTo(display->getIngameCursor());
	  break;
	}
      if (event.type != SDL_KEYDOWN)
	return;
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
  //  perso->render(game);
}

void PlayState::draw(void)
{
  display->render();
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

Display *PlayState::getDisplay()
{
  return (display);
}
