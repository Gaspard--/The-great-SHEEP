//
// main.cpp for  in /home/buffat_b/sdl
//
// Made by
// Login   <buffat_b@epitech.net>
//
// Started on  Thu Jun  9 15:26:15 2016
// Last update Thu Jun  9 15:43:56 2016 Jakob Kellendonk
//

#include <SDL2/SDL.h>
#include <stdio.h>

int		main()
{
  SDL_Window*	pWindow = NULL;

  /* Initialisation simple */
  if (SDL_Init(SDL_INIT_VIDEO))
    {
      fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
      return (-1);
    }

  /* Création de la fenêtre */
  pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
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
