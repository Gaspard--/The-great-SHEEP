#include <SDL2/SDL.h>
#include <vector>
#include "top_header.hpp"
#include "game.hpp"
#include "gamestate.hpp"
#include "menustate.hpp"
#include "playstate.hpp"

using namespace std;

//
// Constructor/Destructor
//
Game::Game()
{
  if (SDL_Init(SDL_INIT_VIDEO))
    {
      fprintf(stderr, "Failed to initialise SDL : (%s)\n", SDL_GetError());
      exit(-1);
    }

  // Create widnow
  window = SDL_CreateWindow("The great SHEEP.",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    WINDOW_WIDTH,
			    WINDOW_HEIGHT,
			    SDL_WINDOW_SHOWN);
  if (!window)
    {
      fprintf(stderr,"Failed to open a window : (%s)\n", SDL_GetError());
      exit(-1);
    }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
    {
      fprintf(stderr,"Failed to create renderer : (%s)\n", SDL_GetError());
      exit(-1);
    }
  running = true;
  this->changeState(new PlayState);
}

Game::~Game()
{
  while (states.empty() != true)
    {
      this->popState();
    }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

//
// Game flow methods
//
void	Game::mainLoop()
{
  while (running == true)
    {
      this->handleEvent();
      this->update();
      this->draw();
    }
}

void	Game::handleEvent()
{
  states.back()->handleEvent();
}

void	Game::update()
{
  states.back()->update();
}

void	Game::draw()
{
  states.back()->draw();
}

//
// Handling game states methods
//
void	Game::changeState(GameState *newState)
{
  if (states.empty() == false)
    {
      states.back()->destroy();
      delete states.back();
      states.pop_back();
    }
  states.push_back(newState);
  states.back()->init(this);
}

void	Game::pushState(GameState *newState)
{
  if (states.empty() == false)
    {
      states.back()->pause();
    }
  states.push_back(newState);
  states.back()->init(this);
}

void	Game::popState()
{
  if (states.empty() == false)
    {
      states.back()->destroy();
      delete states.back();
      states.pop_back();
    }
  if (states.empty() == false)
    {
      states.back()->resume();
    }
}

//
// Leave the game
//
void	Game::quit()
{
  running = false;
}
