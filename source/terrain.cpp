#include "top_header.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "object.hpp"
#include "character.hpp"

Terrain::Terrain()
{
  world_dimension.data[0] = 500;
  world_dimension.data[1] = 500;

  tiles.reserve(world_dimension.data[0] * world_dimension.data[1]);

  orderTiles();
}

Terrain::~Terrain()
{
  tiles.clear();
}

void	Terrain::orderTiles(void)
{
  int	size;
  int	i;

  size = world_dimension.data[0] * world_dimension.data[1];
  i = 0;
  while (i < size)
    {
      tiles[i].type = rand() % 5;
      tiles[i].x = i % world_dimension.data[0];
      tiles[i].y = i / world_dimension.data[0];
      i = i + 1;
    }
}

bool	Terrain::isTile(int x, int y)
{
  if (y > world_dimension[1])
    std::cout << "YOLOYOLOYOLOYOLOYOLOYOLOYOLOYOLOYOLOYOLOYOLOYOLO" << std::endl;

  if (x < 0 || x > world_dimension.data[0]
      || y < 0 || y > world_dimension.data[1])
    return (0);
  return (1);
}

const Tile&	Terrain::getTile(int x, int y)
{
  return (tiles[y * world_dimension.data[0] + x]);
}
