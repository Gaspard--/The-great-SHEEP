#ifndef TILE_HPP_
# define TILE_HPP_

#include "vect.hpp"

class Tile
{
public:
  int id;
  Vect <2u, int> pos;
  int height;
};

#endif // !TILE_HPP_
