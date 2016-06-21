#include "terrain_generator.hpp"
#include "tile.hpp"

TerrainGenerator::TerrainGenerator() : height(123456), temperature(123)
{
}

TerrainGenerator::~TerrainGenerator()
{
}

int TerrainGenerator::getNoise(Vect<2u, int> position, Random& random,
			       unsigned int snap, unsigned int range)
{
  Vect<2u, int> pos(position / snap);
  Vect<2u, int> subpos(position - pos * snap);

  return (int((((random.randomFrom(pos) % range) * (snap - subpos[0])
	    + (random.randomFrom(pos + Vect<2u, int>(1, 0)) % range) * subpos[0]) * (snap - subpos[1])
	   + ((random.randomFrom(pos + Vect<2u, int>(0, 1)) % range) * (snap - subpos[0])
	      + (random.randomFrom(pos + Vect<2u, int>(1, 1)) % range) * subpos[0]) * subpos[1]) / (snap * 4)));
}


Tile TerrainGenerator::genTile(Vect<2u, int> position)
{
  Tile tile;

  tile.id = (getNoise(position, temperature, 8, 8)
    + getNoise(position, temperature, 4, 4)
    + getNoise(position, temperature, 4, 2)) / 4;
  tile.height = getNoise(position, height, 8, 8)
    + getNoise(position, height, 4, 4)
    + getNoise(position, height, 2, 2)
    + getNoise(position, height, 1, 1);
  tile.pos = position;
  return (tile);
}
