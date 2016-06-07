#ifndef TILE_HPP_
# define TILE_HPP_

class	Tile
{
public:
  unsigned int	value;

  Tile();
  Tile(int value);
  int		isSolid();
};

#endif // TILE_HPP_
