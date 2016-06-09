#include "display.hpp"

void	Display::render()
{
  SDL_RenderPresent(renderer);
}

Display::Display()
{
  if (SDL_Init(SDL_INIT_VIDEO))
    {
      fprintf(stderr, "Échec de l'initialisation de la SDL : (%s)\n", SDL_GetError());
      exit(-1);
    }
  /* Création de la fenêtre */
  window = SDL_CreateWindow("The great SHEEP.",
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     640,
			     480,
			     SDL_WINDOW_SHOWN);
  if (!window)
    {
      fprintf(stderr,"Échec de l'ouverture de la fenetre : (%s)\n", SDL_GetError());
      exit(-1);
    }
  /*Création render */
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  /* création texture */
  textures[display::TEXTURE_COEUR] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);
}

Display::~Display()
{
  SDL_Quit();
}
