#ifndef TERRAIN_GENERATOR_HPP_
# define TERRAIN_GENERATOR_HPP_

# include <iostream>
# include <cmath>
# include "vect.hpp"
# include "random.hpp"

class Tile;

class TerrainGenerator
{
public:
  TerrainGenerator(void);
  ~TerrainGenerator(void);
  unsigned int getBiome(Vect<2u, unsigned int> position, Random& random);
  unsigned int getNoise(Vect<2u, unsigned int> position, Random& random,
	       unsigned int snap);
  Tile genTile(Vect<2u, int> position);
private:
  Random height;
  Random temperature;
};

#endif // !TERRAIN_GENERATOR_HPP_
