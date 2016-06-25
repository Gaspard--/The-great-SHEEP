#ifndef TERRAIN_HPP_
# define TERRAIN_HPP_

# include <vector>
# include <iostream>
# include <cstdlib>

# include "vect.hpp"
# include "terrain_generator.hpp"
# include "tile.hpp"
# include "chunk.hpp"

class Terrain
{
private:
  std::vector<Chunk> chunks;
  TerrainGenerator terrainGenerator;

public:
  Terrain(void);
  ~Terrain(void);

  Tile const &getTile(int x, int y);
  void orderTiles(Tile tiles[16], Vect<2, int> pos);
  int getChunk(Vect<2, int>);
  void createChunk(Vect<2, int>);
};

#endif // !TERRAIN_HPP_
