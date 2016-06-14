#ifndef PLAYSTATE_HPP_
# define PLAYSTATE_HPP_

# include "gamestate.hpp"

// Forward declaration
class Display;
class Terrain;

/*
** INHERITED FROM GAMESTATE!! => check gamestate.hpp for more details about
** the following functions
** PlayState : Gamestate for the menu
*/
class PlayState: public GameState
{
public:
  // Constructor/Destructor
  ~PlayState() {};
  void		init(Game *game);
  void		destroy();

  // Gamestate flow
  void		handleEvent();
  void		update();
  void		draw();
  void		pause();
  void		resume();

private:
  // Main class
  Game		*game;
  Display	*display;
  Terrain	*terrain;
};

#endif /* !PLAYSTATE_HPP_ */
