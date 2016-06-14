#include <SDL2/SDL.h>
#include <stdio.h>
#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "vect.hpp"

int		main()
{
  Game		*game = new Game();

  game->mainLoop();
  delete game;
  return (0);
}
