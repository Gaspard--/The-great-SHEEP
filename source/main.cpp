#include <SDL2/SDL.h>
#include <stdio.h>
#include "display.hpp"
#include "terrain.hpp"
#include "vect.hpp"

int		main()
{
  Display	*display = new Display();
  Terrain	*terrain = new Terrain();
  SDL_Event	event;


  event.type = 0;
  event.key.keysym.sym = 0;
  while (event.type != SDL_QUIT && event.key.keysym.sym != SDLK_ESCAPE)
    {
      if (event.key.keysym.sym == SDLK_UP)
      	display->moveCamera(0, -10);
      else if (event.key.keysym.sym == SDLK_DOWN)
      	display->moveCamera(0, 10);
      else if (event.key.keysym.sym == SDLK_LEFT)
      	display->moveCamera(-10, 0);
      else if (event.key.keysym.sym == SDLK_RIGHT)
      	display->moveCamera(10, 0);

      display->clearScreen(0,0,0);
      display->displayTiles(terrain);
      display->render();


      event.key.keysym.sym = 0;
      SDL_PollEvent(&event);
    }

  delete terrain;
  delete display;
  return (0);
}
