#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <iostream>
# include <vector>
# include <algorithm>

# include "top_header.hpp"
# include "camera.hpp"
# include "texture.hpp"
# include "tile.hpp"

class Terrain;
class Game;
class Renderable;
class PlayState;

class Display
{
private:
  int maxRenderHeight;
  Game &game;
  PlayState &playState;
  std::vector<Renderable *> renderables;
  Texture tileset;
  Camera camera;

public:
  Display(Game &game, PlayState &playstate);
  ~Display();

  template<class T>
  Vect<2u, T> fullIsometrize(Vect<2u, T> const &in)
  {
    return ((in + Vect<2u, T>(-in[1], in[0])) * Vect<2u, T>(60, 30));
  }

  template<class T>
  Vect<2u, T> fullIsometrizeRev(Vect<2u, T> const &in)
  {
    return ((in + Vect<2u, T>(-in[1], in[0])) * Vect<2u, T>(30, 60));
  }

  void render(void);
  void clearScreen(int r, int g, int b);

  void displayRenderable(Renderable const &renderable);
  void addRenderable(Renderable *renderable);
  void removeRenderable(Renderable *renderable);

  Vect <2, double> getCameraPosition() const;
  void setCameraPosition(Vect<2, double> newPosition);
  void moveCamera(Vect<2, double> offset);

  Vect <2, double> getIngameCursor() const;

  void transformation(Tile const &);

  void displayTile(SDL_Rect const &, Tile const &);
  void displayLine(Terrain &terrain, Vect<2u, int> const &, Vect<2u, int> pos, bool cut);
  void displayLines(Terrain &terrain, Vect<2u, int> const &);
  void displayTiles(Terrain &terrain);

};

#endif
