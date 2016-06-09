#include <SDL2/SDL.h>
#include <stdio.h>
#include "display.hpp"

int		main()
{
  Display	*display = new Display();

  display->render();
  SDL_Delay(300);
  delete display;
  return (0);
}
