#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <iostream>
# include <vector>
# include <cmath>

# include "camera.hpp"
# include "texture.hpp"

class Tile;
class Terrain;
class Game;
class Renderable;
class PlayState;

namespace display
{

  enum texture_names
    {
      TEXTURE_GRASS_01,
      TEXTURE_GRASS_02,
      TEXTURE_DRY_01,
      TEXTURE_DRY_02,
      TEXTURE_WATER_01,
      TEXTURE_MAX,
    };

  template<class T>
  Vect<2u, T> fullIsometrize(Vect<2u, T> in)
  {
    return ((in + Vect<2u, T>(-in[1], in[0])) * Vect<2u, T>(60, 30));
  }
};

class Display
{
private:
  int maxRenderHeight;
  Game *game;
  PlayState *playState;
  std::vector<Renderable *> renderables;
  Texture tileset;
  Texture textures[display::TEXTURE_MAX];
  Camera camera;

public:
  Display(Game *game, PlayState *playstate);
  ~Display(void);

  void render(void);
  void clearScreen(int r, int g, int b);
  void moveCamera(double x, double y);
  void setCamera(double x, double y);
  void displayLine(Terrain &terrain, SDL_Rect const &);
  void displayLine2(Terrain &terrain, SDL_Rect const &, int x, int y, int line);
  void displayTile(SDL_Rect const &, Tile const &);
  void transformation(Tile const &);
  void smoothScrolling(SDL_Rect&) const;
  void tileScale(SDL_Rect&) const;
  void centerBoard(SDL_Rect&) const;
  void fixBoard(SDL_Rect&) const;
  void isometrize(SDL_Rect&) const;
  void displayTiles(Terrain &terrain);
  void displayRenderable(Renderable *renderable);
  void addRenderable(Renderable *renderable);
  void removeRenderable(Renderable *renderable);

  Vect <2, double> const &getCamera() const;
  Vect <2, double> const getIngameCursor() const;
};

#endif
