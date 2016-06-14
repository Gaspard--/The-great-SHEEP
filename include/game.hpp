#ifndef GAME_HPP_
# define GAME_HPP_

# include <vector>
# include "display.hpp"
# include "terrain.hpp"
# include "gamestate.hpp"

/*
** Game class: contains WINDOW / RENDERER
** => handles gamestates
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
  void				changeState(IGameState *state);
  void				pushState(IGameState *state);
  void				popState();

  // Leave the game
  void				quit();

  SDL_Window			*window;
  SDL_Renderer			*renderer;

private:
  //States stack
  std::vector<IGameState*>	states;

  // True when running, false when quitting
  bool				running;
};

#endif /* !GAME_HPP_ */
