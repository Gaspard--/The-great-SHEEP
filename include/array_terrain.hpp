#ifndef ARRAY_TERRAIN_HPP_
# define ARRAY_TERRAIN_HPP_

# include "terrain.hpp"
# include "tile.hpp"
# include <iostream>

template<unsigned int WIDTH, unsigned int HEIGHT>
class		ArrayTerrain:
  public	Terrain
{
public:
  Tile		tiles[WIDTH][HEIGHT];
  Tile		*outOfBound;
  Tile		*getTile(int x, int y)
  {
    if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
      return (outOfBound);
    return (&tiles[x][y]);
  }
  
};

#endif // ARRAY_TERRAIN_HPP_
