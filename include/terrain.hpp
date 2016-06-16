#ifndef TERRAIN_HPP_
# define TERRAIN_HPP_

# include <vector>
# include <iostream>
# include <cstdlib>

# include "vect.hpp"

class Tile;

class Terrain
{
public:
  Terrain(void);
  ~Terrain(void);

  bool isTile(int x, int y) const;
  Tile const &getTile(int x, int y) const;
  void orderTiles(void);

private:
  std::vector<Tile> tiles;
  Vect <2, int > world_dimension;
};

#endif // !TERRAIN_HPP_
