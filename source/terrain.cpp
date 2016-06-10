#include "terrain.hpp"
#include "tile.hpp"

Terrain::Terrain()
{
}

Tile	Terrain::getTile(int x, int y)
{
  Tile	tile;

  tile.texture = ((x ^ y) & 1) ? TEXTURE_COEUR : TEXTURE_POKEMON;
  tile.height = x;
  return (tile);
}
