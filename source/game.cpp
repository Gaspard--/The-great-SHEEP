#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "top_header.hpp"
#include "game.hpp"
#include "gamestate.hpp"
#include "menustate.hpp"
#include "playstate.hpp"

//
// Constructor/Destructor
//
Game::Game()
{
  if (SDL_Init(SDL_INIT_VIDEO))
    {
      std::cerr << "Failed to initialise SDL : " << SDL_GetError() << std::endl;
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
      std::cerr << "Failed to open a window : " << SDL_GetError() << std::endl;
      exit(-1);
    }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
    {
      std::cerr << "Failed to create renderer : " << SDL_GetError() << std::endl;
      exit(-1);
    }
  running = true;
  this->changeState(new MenuState());
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
      SDL_Delay(10);
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
  if (!states.empty())
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
  if (!states.empty())
    {
      states.back()->pause();
    }
  states.push_back(newState);
  states.back()->init(this);
}

void	Game::popState()
{
  if (!states.empty())
    {
      states.back()->destroy();
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
void	Game::quit()
{
  running = false;
}
