#ifndef TILE_HPP_
# define TILE_HPP_

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
  int	number;
};

#endif // !TILE_HPP_
