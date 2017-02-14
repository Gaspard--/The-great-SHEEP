#ifndef GAMESTATE_HPP_
# define GAMESTATE_HPP_

# include <string>
# include <SDL2/SDL.h>

// Forward declaration
class Game;

/*
** GameState abstract class
*/
class GameState
{
public:
  GameState(Game &game) : game(game) {};
  virtual ~GameState() {};

  // Write your Event handler in this function
  virtual void handleEvent(void) = 0;

  // Called before draw()
  virtual void update(void) = 0;

  // Render in this function
  virtual void draw(void) = 0;

  // Useless for now
  virtual void pause(void) = 0;
  virtual void resume(void) = 0;

  Game &game;
};

#endif /* !GAMESTATE_HPP_ */
