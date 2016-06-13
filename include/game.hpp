#ifndef GAME_HPP_
# define GAME_HPP_

# include <vector>
# include "gamestate.hpp"
# include "display.hpp"
# include "terrain.hpp"

/*
** Game class: contains main classes, handles gamestates
*/

class	Game
{
public:
  Game();
  ~Game();

  // Main loop called in main()
  void				mainLoop();

  // Game flow
  void				handleEvent();
  void				update();
  void				draw();

  // Game States
  void				changeState(GameState *state);
  void				pushState(GameState *state);
  void				popState();

  // Leave the game
  void				quit();

private:
  //States stack
  std::vector<GameState*>	states;

  // main classes
  Display			*display;
  Terrain			*terrain;

  bool				running;
};

#endif /* !GAME_HPP_ */
