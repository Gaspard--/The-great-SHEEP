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
  void				changeState(GameState *state);
  void				pushState(GameState *state);
  void				popState();

  // Leave the game
  void				quit();

  /* Returns a pointer to the renderer */
  SDL_Renderer *getRenderer() {
    return renderer;
  }

  Vect<2, int> getWindowSize() {
    int x, y;
    SDL_GetWindowSize(window, &x, &y);
    return Vect<2, int>(x, y);
  };

  int getWindowWidth() {
    return getWindowSize()[0];
  }

  int getWindowHeight() {
    return getWindowSize()[1];
  }

private:
  //States stack
  std::vector<GameState*>	states;

  // True when running, false when quitting
  bool				running;

  SDL_Window			*window;
  SDL_Renderer			*renderer;
};

#endif /* !GAME_HPP_ */
