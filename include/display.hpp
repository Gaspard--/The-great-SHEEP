#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

namespace display
{
  enum texture_names
    {
      TEXTURE_COEUR,
      TEXTURE_MAX
    };
};

class Display
{
public:
  Display();
private:
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture	*textures[display::TEXTURE_MAX];
};

#endif
