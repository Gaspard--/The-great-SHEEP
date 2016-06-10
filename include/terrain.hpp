#ifndef TERRAIN_HPP_
# define TERRAIN_HPP_

class	Tile;

class	Terrain
{
public:
  Terrain();
  Tile	getTile(int x, int y);
}

#endif // !TERRAIN_HPP_
