#ifndef PLAYSTATE_HPP_
# define PLAYSTATE_HPP_

# include <iostream>

# include "gamestate.hpp"

// Forward declaration
class Display;
class Terrain;
class EntityHandler;
class Logic;
class Perso;

/*
** INHERITED FROM GAMESTATE!! => check gamestate.hpp for more details about
** the following functions
** PlayState : Gamestate for the actual game!
*/
class PlayState: public IGameState
{
private:
  // Main class
  Game *game;
  Display *display;
  Terrain *terrain;
  EntityHandler *entityHandler;
  Logic *logic;
  Perso		*perso;

public:
  // Constructor/Destructor
  PlayState(Game *game);
  ~PlayState();

  // Gamestate flow
  void handleEvent(void);
  void update(void);
  void draw(void);
  void pause(void);
  void resume(void);


  // getters
  Logic *getLogic();
  Terrain *getTerrain();
  EntityHandler *getEntityHandler();
  Display *getDisplay();
};

#endif /* !PLAYSTATE_HPP_ */
