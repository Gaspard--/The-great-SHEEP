#ifndef PLAYSTATE_HPP_
# define PLAYSTATE_HPP_

# include <iostream>

# include "gamestate.hpp"
# include "display.hpp"
# include "terrain.hpp"
# include "logic.hpp"
# include "entity_handler.hpp"
# include "perso.hpp"

// Forward declaration
// class Display;
// class Terrain;
// class EntityHandler;
// class Logic;
// class Perso;

/*
** INHERITED FROM GAMESTATE!! => check gamestate.hpp for more details about
** the following functions
** PlayState : Gamestate for the actual game!
*/
class PlayState: public GameState
{
private:
  // Main class
  Display display;
  Terrain terrain;
  EntityHandler entityHandler;
  Logic logic;
  Perso perso;
  Perso perso2;

public:
  // Constructor/Destructor
  PlayState(Game &game);
  ~PlayState();

  // Gamestate flow
  void handleEvent(void);
  void update(void);
  void draw(void);
  void pause(void);
  void resume(void);


  // getters
  Logic& getLogic();
  Terrain& getTerrain();
  EntityHandler& getEntityHandler();
  Display& getDisplay();
};

#endif /* !PLAYSTATE_HPP_ */
