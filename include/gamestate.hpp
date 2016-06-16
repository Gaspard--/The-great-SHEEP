#ifndef GAMESTATE_HPP_
# define GAMESTATE_HPP_

# include <string>
# include <SDL2/SDL.h>

// Forward declaration
class Game;

/*
** IGameState interface
*/
class IGameState
{
public:
  // Constructor/Destructor
  virtual ~IGameState(void) {}; // <= BUG ???
  virtual void init(Game *game) = 0;
  virtual void destroy(void) = 0;

  // Write your Event handler in this function
  virtual void handleEvent(void) = 0;

  // Called before draw()
  virtual void update(void) = 0;

  // Render in this function
  virtual void draw(void) = 0;

  // Useless for now
  virtual void pause(void) = 0;
  virtual void resume(void) = 0;

private:
  Game *game;
};

#endif /* !GAMESTATE_HPP_ */
