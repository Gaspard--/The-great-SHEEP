#include "terrain_generator.hpp"
#include "tile.hpp"

TerrainGenerator::TerrainGenerator() : height(123456), temperature(123)
{
}

TerrainGenerator::~TerrainGenerator()
{
}

unsigned int TerrainGenerator::getBiome(Vect<2u, unsigned int> position, Random& random)
{
  unsigned int snap(16u);
  unsigned int mindist;
  unsigned int result;
  Vect<2u, unsigned int> off(0u, 0u);
  unsigned int i(0u);

  while (off[0] <= 2u)
    {
      off[1] = 0u;
      while (off[1] <= 2u)
	{
	  Vect<2u, unsigned int> biomePos(position / snap + off - Vect<2u, unsigned int>(1u, 1U));
	  uint64_t tmp(random.randomFrom(biomePos));
	  Vect<2u, unsigned int> neighboor(biomePos * snap +
					   Vect<2u, unsigned int>(tmp & (snap - 1u), (tmp >> 16u) & (snap - 1u)));

	  if (!i || (neighboor - position).length() < mindist)
	    {
	      result = (tmp / 17) & 3u;
	      mindist = (neighboor - position).length();
	    }
	  i = i + 1u;
	  off[1] = off[1] + 1u;
	}
      off[0] = off[0] + 1u;
    }
  return (result);
}

unsigned int TerrainGenerator::getNoise(Vect<2u, unsigned int> position, Random& random,
					unsigned int snap, unsigned int range)
{
  unsigned int mindist;
  unsigned int result;
  Vect<2u, unsigned int> off(0u, 0u);
  unsigned int i(0u);

  while (off[0] <= 2u)
    {
      off[1] = 0u;
      while (off[1] <= 2u)
	{
	  Vect<2u, unsigned int> biomePos(position / snap + off - Vect<2u, unsigned int>(1u, 1U));
	  uint64_t tmp(random.randomFrom(biomePos));
	  Vect<2u, unsigned int> neighboor(biomePos * snap +
					   Vect<2u, unsigned int>(tmp % snap, (tmp >> 16u) % snap));

	  if (!i || (neighboor - position).length() < mindist)
	    {
	      mindist = (neighboor - position).length();
	      result = mindist;
	    }
	  i = i + 1u;
	  off[1] = off[1] + 1u;
	}
      off[0] = off[0] + 1u;
    }
  return (result);
}


Tile TerrainGenerator::genTile(Vect<2u, int> position)
{
  Vect<2u, unsigned int> genPos(Vect<2u, long int>(position) + Vect<2u, long int>(0x80000000, 0x80000000));
  Tile tile;

  tile.id = getBiome(genPos, temperature);
  tile.height = getNoise(genPos, height, 16, 8) / 16
    + getNoise(genPos, height, 8, 8) / 16;
  tile.pos = genPos;
  return (tile);
}
