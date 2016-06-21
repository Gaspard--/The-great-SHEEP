#include "terrain_generator.hpp"
#include "tile.hpp"

TerrainGenerator::TerrainGenerator()
{
}

TerrainGenerator::~TerrainGenerator()
{
}

Tile TerrainGenerator::genTile(Vect<2u, int> position)
{
  Tile tile;

  tile.id = rand() % 4;
  tile.height = (sin((position[0]) * 0.3) * sin((position[1]) * 0.3) + 1) * 5;
  tile.pos = position;
  return (tile);
}
