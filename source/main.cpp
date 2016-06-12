#include <SDL2/SDL.h>
#include <stdio.h>
#include "display.hpp"
#include "terrain.hpp"

int		main()
{
  Display	*display = new Display();
  Terrain	*terrain = new Terrain();
  SDL_Event	event;

  event.type = 0;
  while (event.type != SDL_QUIT && event.key.keysym.sym != SDLK_ESCAPE)
    {
      display->clearScreen(0, 0, 0);
      display->displayTiles(terrain);
      display->displayObjects(terrain);

      //random disposition of characters
      terrain->disposeCharacters();
      display->displayCharacters(terrain);
      display->render();
      SDL_Delay(500);
      SDL_PollEvent(&event);
    }

  delete terrain;
  delete display;
  return (0);
}
