#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <SDL_image.h>
# include <stdio.h>

namespace display
{
  enum texture_names
    {
      TEXTURE_COEUR,
      TEXTURE_POKEMON,
      TEXTURE_MAX
    };
};

class Display
{
public:
  Display();
  ~Display();

  void	render();

private:
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture	*textures[display::TEXTURE_MAX];
};

#endif
