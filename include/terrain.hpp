#ifndef TERRAIN_HPP_
# define TERRAIN_HPP_

# include "tile.hpp"

class	Terrain
{
public:
  virtual Tile	*getTile(int x, int y) = 0;
};

#endif // TERRAIN_HPP_
