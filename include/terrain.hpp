#ifndef TERRAIN_HPP_
# define TERRAIN_HPP_

# include <vector>
# include <cstdlib>
# include "vect.hpp"

class	Tile;

class	Terrain
{
public:
  Terrain();
  ~Terrain();

  bool	isTile(int x, int y);
  const Tile&	getTile(int x, int y);
  void	orderTiles(void);

private:
  std::vector<Tile> tiles;
  Vect <2, int > world_dimension;
};

#endif // !TERRAIN_HPP_
