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
  perso = new Perso(game->getRenderer());
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
void	PlayState::handleEvent()
{
  SDL_Event		event;
  Vect<2u, double>	tmp;

  if (!SDL_PollEvent(&event))
    return;
  if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
    game->quit();
  else if (event.key.keysym.sym == SDLK_UP)
    display->moveCamera(0, -0.2);
  else if (event.key.keysym.sym == SDLK_DOWN)
    display->moveCamera(0, 0.2);
  else if (event.key.keysym.sym == SDLK_LEFT)
    display->moveCamera(-0.2, 0);
  else if (event.key.keysym.sym == SDLK_RIGHT)
    display->moveCamera(0.2, 0);
  if (event.type == SDL_MOUSEBUTTONDOWN)
    {
      tmp = Vect<2u, double>(event.button.x, event.button.y);
      perso->moveTo(tmp);
    }
}

void	PlayState::update()
{
  // Display tiles
  display->clearScreen(0, 0, 0);
  display->displayTiles(terrain);

  // Display perso
  perso->update();
  this->renderPerso();
}

void	PlayState::draw()
{
  SDL_RenderPresent(game->getRenderer());
}

void	PlayState::pause()
{
  // Do nothing
}

void	PlayState::resume()
{
  // Do nothing
}

void	PlayState::renderPerso()
{
  SDL_Rect	rect;
  std::vector<Renderable>	renderable = perso->getRenderable();
  Vect<2u, double>		size = (*renderable.back().dimensions);
  Vect<2u, double>		pos = perso->getPosition();

  rect.w = size[0];
  rect.h = size[1];
  rect.x = pos[0];
  rect.y = pos[1];
  SDL_RenderCopy(game->getRenderer(), renderable[0].texture, NULL, &rect);
}
