#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <vector>
# include "camera.hpp"

class Camera;
class Tile;
class Object;
class Character;
class Terrain;

namespace display
{
  enum texture_names
    {
      TEXTURE_BASIC_TILESET,
      TEXTURE_BASIC_OBJECT_SET,
      TEXTURE_BASIC_CHARACTER_SET,
      TEXTURE_TILE_GRASS,
      TEXTURE_TILE_WATER,
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
  void	displayTiles(Terrain *terrain);
  void	isometrize(SDL_Rect&);
  void	tileScale(SDL_Rect&);
  void	centerBoard(SDL_Rect&);
  void	fixBoard(SDL_Rect&, const SDL_Rect&);

  void	movementShake(SDL_Rect&, const SDL_Rect&);

  void	displayTest();

  void	moveCamera(int x, int y);


private:
  SDL_Window	*window;
  SDL_Renderer	*renderer;
  SDL_Texture	*textures[display::TEXTURE_MAX];
  Camera	camera;
};

#endif
