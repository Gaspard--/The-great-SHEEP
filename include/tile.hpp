#ifndef TILE_HPP_
# define TILE_HPP_

#include "vect.hpp"

struct Tile
{
  enum class Type
  {
    GRASS,
    HILL,
    ROAD,
    WATER,
    SHORE,
    MAX,
  };

  static const int typeCount = static_cast<int>(Type::MAX);

  Type type;
  Vect<2, int > pos;
  int x;
  int y;
};

#endif // !TILE_HPP_
