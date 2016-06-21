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
  int getHeight(Vect<2u, int> position, int snap, int range);
  Tile genTile(Vect<2u, int> position);
private:
  Random random;
};

#endif // !TERRAIN_GENERATOR_HPP_
