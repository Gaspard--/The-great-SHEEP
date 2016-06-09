#include "display.hpp"

void	Display::render()
{
  SDL_RenderCopy(renderer, textures[display::TEXTURE_POKEMON], NULL, NULL);
  SDL_RenderPresent(renderer);
}

Display::Display()
{

  if (SDL_Init(SDL_INIT_VIDEO))
    {
      fprintf(stderr, "Failed to initialise SDL : (%s)\n", SDL_GetError());
      exit(-1);
    }

  // Create widnow
  window = SDL_CreateWindow("The great SHEEP.",
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     640,
			     480,
			     SDL_WINDOW_SHOWN);
  if (!window)
    {
      fprintf(stderr,"Failed to open a window : (%s)\n", SDL_GetError());
      exit(-1);
    }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
    {
      fprintf(stderr,"Failed to create renderer : (%s)\n", SDL_GetError());
      exit(-1);
    }

  // Load textures
  int		i;

  textures[display::TEXTURE_COEUR] = IMG_LoadTexture(renderer, "assets/icon_heart.png");

  textures[display::TEXTURE_POKEMON] = IMG_LoadTexture(renderer, "assets/pok.png");
  i = 0;
  while (i < display::TEXTURE_MAX)
    {
      if (!textures[i])
	{
	  fprintf(stderr, "Failed to open a texture : (%s)\n", SDL_GetError());
	  exit(-1);
	}
      i = i + 1;
    }
}

Display::~Display()
{
  SDL_DestroyTexture(textures[display::TEXTURE_COEUR]);
  SDL_DestroyTexture(textures[display::TEXTURE_POKEMON]);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
