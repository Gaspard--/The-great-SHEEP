#include "top_header.hpp"
#include "game.hpp"
#include "gamestate.hpp"
#include "menustate.hpp"
#include "playstate.hpp"

//
// Constructor/Destructor
//
Game::Game(void) : timer(*this)
{
  if (SDL_Init(SDL_INIT_VIDEO))
    {
      std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
      exit(-1);
    }

  // Create window
  window = SDL_CreateWindow("The great SHEEP.",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    1200,
			    800,
			    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (!window)
    {
      std::cerr << "Failed to open a window: " << SDL_GetError() << std::endl;
      exit(-1);
    }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer)
    {
      std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
      exit(-1);
    }
  running = true;
  changeState(new MenuState(*this));
}

Game::~Game(void)
{
  while (states.empty() != true)
    {
      popState();
    }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

//
// Game flow methods
//
void Game::mainLoop(void)
{
  while (running == true)
    {
      handleEvent();
      update();
      timer.update();
      if (timer.getShow())
	timer.showFps();
      draw();
    }
}

void Game::handleEvent(void)
{
  states.back()->handleEvent();
}

void Game::update(void)
{
  states.back()->update();
}

void Game::draw(void)
{
  states.back()->draw();
}

void Game::toggleShowFps(void)
{
  timer.toggleShow();
}

//
// Handling game states methods
//
void Game::changeState(GameState *newState)
{
  if (!states.empty())
    {
      delete states.back();
      states.pop_back();
    }
  states.push_back(newState);
}

void Game::pushState(GameState *newState)
{
  if (!states.empty())
    {
      states.back()->pause();
    }
  states.push_back(newState);
}

void Game::popState(void)
{
  if (!states.empty())
    {
      delete states.back();
      states.pop_back();
    }
  if (!states.empty())
    {
      states.back()->resume();
    }
}

//
// Leave the game
//
void Game::quit(void)
{
  running = false;
}
