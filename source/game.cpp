#include <SDL2/SDL.h>
#include <vector>
#include "game.hpp"

using namespace std;

//
// Constructor/Destructor
//
Game::Game()
{
  display = new Display();
  terrain = new Terrain();
  running = true;
}

Game::~Game()
{
  delete terrain;
  delete display;
  while (states.empty() != true)
    {
      delete states.back();
      states.pop_back();
    }
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
      delete states.back();
      states.pop_back();
    }
  states.push_back(newState);
}

void	Game::pushState(GameState *newState)
{
  if (states.empty() == false)
    {
      states.back()->pause();
    }
  states.push_back(newState);
}

void	Game::popState()
{
  if (states.empty() == false)
    {
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
