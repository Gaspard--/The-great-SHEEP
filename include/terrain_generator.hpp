#ifndef TERRAIN_GENERATOR_HPP_
# define TERRAIN_GENERATOR_HPP_

# include <iostream>
# include "vect.hpp"

class Tile;

class TerrainGenerator
{
  public:
    TerrainGenerator(void);
    ~TerrainGenerator(void);
    Tile genTile(Vect<2u, int> position);
  private:
};

#endif // !TERRAIN_GENERATOR_HPP_
