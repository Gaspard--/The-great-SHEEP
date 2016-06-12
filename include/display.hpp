#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <stdio.h>
# include <vector>

class Terrain;

namespace display
{
  enum texture_names
    {
      TEXTURE_COEUR,
      TEXTURE_POKEMON,
      TEXTURE_BASIC_TILESET,
      TEXTURE_BASIC_OBJECT_SET,
      TEXTURE_BASIC_CHARACTER_SET,
      TEXTURE_MAX
    };
};

class Display
{
public:
  Display();
  ~Display();

  void	render();
  void	clearScreen(int r, int g, int b);
  void	displayTiles(Terrain*);
  void	displayObjects(Terrain*);
  void	displayCharacters(Terrain*);

private:
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture	*textures[display::TEXTURE_MAX];
};

#endif
