#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include "camera.hpp"

class Camera;
class Tile;
class Terrain;
class Game;

namespace display
{
  enum texture_names
    {
      TEXTURE_TILE_GRASS,
      TEXTURE_TILE_WATER,
      TEXTURE_MAX
    };
};

class Display
{
public:
  Display(Game *game);
  ~Display();

  void	render();
  void	clearScreen(int r, int g, int b);
  void	moveCamera(double x, double y);
  void	displayLine(Terrain *terrain, const SDL_Rect&);
  void	affTile(const SDL_Rect&, const Tile&);
  void	transformation(const Tile&);
  void	smoothScrolling(SDL_Rect&);
  void	tileScale(SDL_Rect&);
  void	centerBoard(SDL_Rect&);
  void	fixBoard(SDL_Rect&);
  void	isometrize(SDL_Rect&);
  void	displayTiles(Terrain *terrain);

  const Vect <2, double>& getCamera();
  const Vect <2, double> getIngameCursor();

private:
  Game	*game;
  SDL_Texture	*textures[display::TEXTURE_MAX];
  Camera	camera;
};

#endif
