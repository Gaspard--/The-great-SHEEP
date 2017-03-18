#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <iostream>
# include <algorithm>

# include "followable_vector.hpp"
# include "top_header.hpp"
# include "camera.hpp"
# include "texture.hpp"
# include "tile.hpp"
# include "follow.hpp"
# include "renderable.hpp"

class Terrain;
class Game;
class PlayState;

class Display
{
private:
  int maxRenderHeight;
  Game &game;
  PlayState &playState;
  Texture tileset;
  Camera camera;

public:
  FollowableVector<Renderable> renderables;
  
  Display(Game &game, PlayState &playstate);
  ~Display();

  void render(void);
  void clearScreen(int r, int g, int b);

  void displayRenderable(Renderable const &renderable);

  void setCameraPosition(Vect<2, double> newPosition);
  void moveCamera(Vect<2, double> offset);

  Vect <2, double> getIngameCursor() const;

  void displayTile(Tile const &);
  void displayLine(Terrain &terrain, Vect<2u, int> pos, bool cut);
  void displayTiles(Terrain &terrain);
};

#endif
