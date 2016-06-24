#include <cassert>
#include "top_header.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "chunk.hpp"
#include <cmath>

using namespace std;

Terrain::Terrain(void) : terrainGenerator()
{
}

Terrain::~Terrain(void)
{
  unsigned int i = 0;
  while (i < chunks.size())
    {
      ++i;
    }
  chunks.clear();
}

int Terrain::getChunk(Vect<2, int> pos)
{
  unsigned int i = 0;

  while (i < chunks.size())
    {
      if (chunks[i].coord == pos)
	return ((int)i);
      ++i;
    }
  return (-1);
}

void Terrain::orderTiles(Tile *tiles, Vect<2, int> pos)
{
  int size = 16 * 16;
  int i = 0;

  while (i < size)
    {
      tiles[i] =
	terrainGenerator.genTile(Vect<2, int>(i % 16, i / 16)
				 + pos * 16);
      ++i;
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
  int i;
  Vect<2, int> pos(x < 0 ? -((-x - 1) >> 4) : x >> 4,
		   y < 0 ? -((-y - 1) >> 4) : y >> 4);

  if ((i = getChunk(pos)) == -1)
    {
      cout << "new chunk " << pos[0] << " " << pos[1] << endl;
      createChunk(pos);
      i = getChunk(pos);
    }
  return (chunks[i].tiles[(y < 0 ? 15 - ((-y - 1) & 15) : y & 15) * 16 +
  			  (x < 0 ? 15 - ((-x - 1) & 15) : x & 15)]);
}
