#include "game.hpp"
#include "display.hpp"
#include "terrain.hpp"
#include "vect.hpp"

int main()
{
  Game game;
  Vect<3u, double> a(2, 2, 3);

  std::cout << a.x() << std::endl;
  game.mainLoop();
  return (0);
}
