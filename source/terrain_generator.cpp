#include "terrain_generator.hpp"
#include "array_terrain.hpp"

Terrain				*terrain_generator::generateTerrain1(int seed)
{
  const int			WIDTH = 60;
  const int			HEIGHT = 60;
  ArrayTerrain<WIDTH, HEIGHT>	*result;
  int				x;
  int				y;

  result = new ArrayTerrain<WIDTH, HEIGHT>();
  result->outOfBound = new Tile(1);
  x = 0;
  while (x < WIDTH)
    {
      y = 0;
      while (y < HEIGHT)
	{
	  result->tiles[x][y] = Tile(((((x % 7) + 7) % 7) >> (((y % 3) + 3) % 3)));
	  y = y + 1;
	}
      x = x + 1;
    }
  return (result);
}
