#ifndef TILE_HPP_
# define TILE_HPP_

#include "vect.hpp"

namespace display
{
    enum tile_names
      {
	TILE_GRASS,
	TILE_HILL,
	TILE_ROAD,
	TILE_WATER,
	TILE_SHORE,
	TILE_MAX
      };
};

struct	Tile
{
  int	type;
  Vect <2, int > pos;
  int	x;
  int	y;
};

#endif // !TILE_HPP_
