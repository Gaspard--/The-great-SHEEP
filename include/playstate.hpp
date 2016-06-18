#ifndef PLAYSTATE_HPP_
# define PLAYSTATE_HPP_

# include <iostream>

# include "gamestate.hpp"

// Forward declaration
class Display;
class Terrain;
class EntityHandler;
class Logic;

/*
** INHERITED FROM GAMESTATE!! => check gamestate.hpp for more details about
** the following functions
** PlayState : Gamestate for the actual game!
*/
class PlayState: public IGameState
{
public:
  // Constructor/Destructor
  ~PlayState(void) {}
  void init(Game *game);
  void destroy(void);

  // Gamestate flow
  void handleEvent(void);
  void update(void);
  void draw(void);
  void pause(void);
  void resume(void);

private:
  // Main class
  Game *game;
  Display *display;
  Terrain *terrain;
  EntityHandler *entityHandler;
  Logic *logic;
};

#endif /* !PLAYSTATE_HPP_ */
