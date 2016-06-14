#ifndef MENUSTATE_HPP_
# define MENUSTATE_HPP_

# include "gamestate.hpp"

/*
** INHERITED FROM GAMESTATE!! => check gamestate.hpp for more details about
** the following functions
** MenuState : Gamestate for the menu
*/
class MenuState: public GameState
{
public:
  // Constructor/Destructor
  ~MenuState() {};
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

  // Menustate's variables
  SDL_Texture	*startButton;
};

#endif /* !MENUSTATE_HPP_ */
