#include "terrain_generator.hpp"
#include "tile.hpp"

TerrainGenerator::TerrainGenerator() : random(123456)
{
}

TerrainGenerator::~TerrainGenerator()
{
}

int TerrainGenerator::getHeight(Vect<2u, int> position, int snap, int range)
{
  Vect<2u, int> pos(position / snap);
  Vect<2u, int> subpos(position - pos * snap);

  return ((((my_random::randomFrom(pos) % range) * (snap - subpos[0])
	    + (my_random::randomFrom(pos + Vect<2u, int>(1, 0)) % range) * subpos[0]) * (snap - subpos[1])
	   + ((my_random::randomFrom(pos + Vect<2u, int>(0, 1)) % range) * (snap - subpos[0])
	      + (my_random::randomFrom(pos + Vect<2u, int>(1, 1)) % range) * subpos[0]) * subpos[1]) / (snap * 4));
}


Tile TerrainGenerator::genTile(Vect<2u, int> position)
{
  Tile tile;

  tile.id = 0 % 4;
  tile.height = getHeight(position, 8, 8)
    + getHeight(position, 4, 4)
    + getHeight(position, 2, 2)
    + getHeight(position, 1, 1);
  tile.pos = position;
  return (tile);
}
