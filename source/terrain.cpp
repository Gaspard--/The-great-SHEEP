#include "top_header.hpp"
#include "terrain.hpp"
#include "tile.hpp"
#include "object.hpp"
#include "character.hpp"

Terrain::Terrain()
{
  width = TILE_WIDTH;
  height = TILE_HEIGHT;
  numberCharacters = 0;
  Tiles.reserve(width * height);
  Objects.reserve(width * height);
  Characters.reserve(width * height);
  disposeTiles();
  disposeObjects();
  disposeCharacters();
}

Terrain::~Terrain()
{
  Tiles.clear();
  Objects.clear();
  Characters.clear();
}

const Tile *Terrain::getTiles(void)
{
  return (Tiles.data());
}

int Terrain::getNumberTiles(void)
{
  return (width * height);
}

void	Terrain::disposeTiles(void)
{
  int	size;
  int	i;

  size = width * height;
  i = 0;
  while (i < size)
    {
      Tiles[i].type = rand() % 5;
      Tiles[i].number = i;
      i = i + 1;
    }
}

const Object *Terrain::getObjects(void)
{
  return (Objects.data());
}

int Terrain::getNumberObjects(void)
{
  return (numberObjects);
}

void	Terrain::disposeObjects(void)
{
  int	i;

  // arbitrary chosen
  numberObjects = 25;
  i = 1;
  while (i < numberObjects)
    {
      Objects[i].type = rand() % 5;
      Objects[i].x = rand() % TILE_WIDTH;
      Objects[i].y = rand() % TILE_HEIGHT;
      i = i + 1;
    }
}

const Character *Terrain::getCharacters(void)
{
  return (Characters.data());
}

int Terrain::getNumberCharacters(void)
{
  return (numberCharacters);
}

void	Terrain::disposeCharacters(void)
{
  int	i;

  Characters[0].type = display::CHARACTER_MAIN;
  Characters[0].x = 15;
  Characters[0].y = 15;

  // arbitrary chosen
  numberCharacters = 10;
  i = 1;
  while (i < numberCharacters)
    {
      Characters[i].type = rand() % 4 + 1;
      Characters[i].x = rand() % WINDOW_WIDTH;
      Characters[i].y = rand() % WINDOW_HEIGHT;
      i = i + 1;
    }
}

Tile	Terrain::getTile(int x, int y)
{
  return (Tiles.at(y * width + x));
}
