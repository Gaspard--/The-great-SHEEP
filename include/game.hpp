#ifndef GAME_HPP_
# define GAME_HPP_

# include <SDL2/SDL.h>
# include <vector>
# include <iostream>

# include "display.hpp"
# include "terrain.hpp"
# include "gamestate.hpp"

/*
** Game class: contains WINDOW / RENDERER
** => handles gamestates
*/

class Game
{
public:
  Game(void);
  ~Game(void);

  // Main loop called in main()
  void mainLoop(void);

  // Game flow
  void handleEvent(void);
  void update(void);
  void draw(void);

  // Game States
  void changeState(IGameState *state);
  void pushState(IGameState *state);
  void popState(void);

  // Leave the game
  void quit(void);

  /* Returns a pointer to the renderer */
  SDL_Renderer *getRenderer(void) const {
    return renderer;
  }

  Vect<2, int> getWindowSize(void) const {
    int x, y;
    SDL_GetWindowSize(window, &x, &y);
    return Vect<2, int>(x, y);
  };

  int getWindowWidth(void) const {
    return getWindowSize()[0];
  }

  int getWindowHeight(void) const {
    return getWindowSize()[1];
  }

private:
  //States stack
  std::vector<IGameState*> states;

  // True when running, false when quitting
  bool running;
  SDL_Window *window;
  SDL_Renderer *renderer;
};

#endif /* !GAME_HPP_ */
