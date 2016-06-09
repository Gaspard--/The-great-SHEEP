#include <SDL2/SDL.h>
#include <stdio.h>
#include "display.hpp"

int		main()
{
  Display	*display = new Display();
  SDL_Event	event;

  display->render();

  while (event.type != SDL_QUIT)
    {
      SDL_PollEvent(&event);
    }

  SDL_Delay(300);
  delete display;
  return (0);
}
