#include "tile.hpp"

Tile::Tile()
{
  this->value = 0;
}

Tile::Tile(int	value)
{
  this->value = value;
}

int	Tile::isSolid()
{
  return (!!(value & 1));
}
