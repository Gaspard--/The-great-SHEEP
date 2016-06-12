#ifndef TERRAIN_HPP_
# define TERRAIN_HPP_

# include <iostream>
# include <vector>
# include <cstdlib>

class	Tile;
class	Object;
class	Character;

class	Terrain
{
public:
  Terrain();
  ~Terrain();

  Tile	getTile(int x, int y);

  const Tile *getTiles(void);
  int getNumberTiles(void);
  void	disposeTiles(void);

  const Object *getObjects(void);
  int getNumberObjects(void);
  void	disposeObjects(void);

  const Character *getCharacters(void);
  int getNumberCharacters(void);
  void	disposeCharacters(void);

private:
  std::vector<Tile> Tiles;
  std::vector<Object> Objects;
  std::vector<Character> Characters;
  int	numberObjects;
  int	numberCharacters;
  int	width;
  int	height;
};

#endif // !TERRAIN_HPP_
