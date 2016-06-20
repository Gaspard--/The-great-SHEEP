#include <cassert>
#include "top_header.hpp"
#include "terrain.hpp"
#include "tile.hpp"

Terrain::Terrain(void)
{
  world_dimension[0] = 500;
  world_dimension[1] = 500;
  tiles.reserve(world_dimension[0] * world_dimension[1]);
  orderTiles();
}

Terrain::~Terrain(void)
{
  tiles.clear();
}

void Terrain::orderTiles(void)
{
  int size = world_dimension[0] * world_dimension[1];
  int i = 0;

  while (i < size)
    {
      tiles[i].id = rand() % 5;
      tiles[i].pos[0] = i % world_dimension[0];
      tiles[i].pos[1] = i / world_dimension[0];
      i = i + 1;
    }
}

bool Terrain::isTile(int x, int y) const
{
  return ((x >= 0 && x < world_dimension[0])
	  && (y >= 0 && y < world_dimension[1]));
}

Tile const &Terrain::getTile(int x, int y) const
{
  return (tiles[y * world_dimension[0] + x]);
}
