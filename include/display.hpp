#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <iostream>

# include "camera.hpp"

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
  ~Display(void);

  void render(void);
  void clearScreen(int r, int g, int b);
  void moveCamera(double x, double y);
  void displayLine(Terrain *terrain, SDL_Rect const &);
  void affTile(SDL_Rect const &, Tile const &);
  void transformation(Tile const &);
  void smoothScrolling(SDL_Rect&) const;
  void tileScale(SDL_Rect&) const;
  void centerBoard(SDL_Rect&) const;
  void fixBoard(SDL_Rect&) const;
  void isometrize(SDL_Rect&) const;
  void displayTiles(Terrain *terrain);

  Vect <2, double> const &getCamera() const;
  Vect <2, double> const getIngameCursor() const;

private:
  Game *game;
  SDL_Texture *textures[display::TEXTURE_MAX];
  Camera camera;
};

#endif
