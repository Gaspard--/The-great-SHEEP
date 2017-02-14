#include "terrain.hpp"
#include "tile.hpp"
#include "chunk.hpp"

Terrain::Terrain(void) : terrainGenerator()
{
}

Terrain::~Terrain(void)
{
  chunks.clear();
}

int Terrain::getChunk(Vect<2, int> pos)
{
  int i(0);

  while (i < (int)chunks.size() && !(chunks[i].coord == pos))
    i = i + 1;
  if (i != (int)chunks.size())
    return (i);
  return (-1);
}

void Terrain::orderTiles(Tile *tiles, Vect<2, int> pos)
{
  constexpr int const size(16 * 16);
  int i(0);

  while (i < size)
    {
      tiles[i] = terrainGenerator.genTile(Vect<2, int>(i % 16, i / 16) + pos * 16);
      i = i + 1;
    }
}

void Terrain::createChunk(Vect<2, int> pos)
{
  Chunk elem;

  elem.coord = pos;
  orderTiles(elem.tiles, pos);
  chunks.push_back(elem);
}

Tile const &Terrain::getTile(int x, int y)
{
  Vect<2u, int> pos(x < 0 ? -((-x - 1) >> 4) - 1 : x >> 4,
		    y < 0 ? -((-y - 1) >> 4) - 1 : y >> 4);
  Vect<2u, int> off(Vect<2u, int>(x, y) - (pos * 16));
  int i(getChunk(pos));

  if (i == -1)
    {
      std::cout << "new chunk " << pos[0] << " " << pos[1] << std::endl;
      createChunk(pos);
      i = getChunk(pos);
    }
  return (chunks[i].tiles[off[1] * 16 + off[0]]);
}
