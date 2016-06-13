#ifndef MENUSTATE_HPP_
# define MENUSTATE_HPP_

# include "gamestate.hpp"

/*
** MenuState : Gamestate for the menu
*/

class MenuState: public GameState
{
public:
  MenuState(Game *game);
  ~MenuState();

  void		handleEvent();
  void		update();
  void		draw();

  void		pause();
  void		resume();

private:
  Game		*game;
  SDL_Texture	*background;
  SDL_Renderer	*renderer;
};

#endif /* !MENUSTATE_HPP_ */
