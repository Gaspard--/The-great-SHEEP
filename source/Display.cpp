Display::Display()
{

  /* Création de la fenêtre */
  window = SDL_CreateWindow("The great SHEEP.",
			     SDL_WINDOWPOS_UNDEFINED,
			     SDL_WINDOWPOS_UNDEFINED,
			     640,
			     480,
			     SDL_WINDOW_SHOWN);

  /*Création render */
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

  /* création texture */
  textures[TEXTURE_COEUR] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1024, 768);

}

Display::~Display()
{
}
