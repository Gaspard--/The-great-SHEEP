#include <SDL2/SDL.h>
#include <stdio.h>
#include "display.hpp"

int		main()
{
  SDL_Window	*pWindow = NULL;

  /* Initialisation simple */
  if (SDL_Init(SDL_INIT_VIDEO))
    {
      fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
      return (-1);
    }

  /* Création de la fenêtre */
  pWindow = SDL_CreateWindow("The great SHEEP.",
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     640,
			     480,
			     SDL_WINDOW_SHOWN);

  if (pWindow)
    {
      /* Attendre trois secondes, que l'utilisateur voie la fenêtre */
      SDL_Delay(3000);
      SDL_DestroyWindow(pWindow);
    }
  else
    fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());

  SDL_Quit();
  return (0);
}
