#include <SDL2/SDL.h>
#include <stdio.h>
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"

int		main()
{
  Game		*game = new Game();

  game->mainLoop();
  delete game;
  return (0);
}
