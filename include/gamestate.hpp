#ifndef GAMESTATE_HPP_
# define GAMESTATE_HPP_

# include <string>
# include <SDL2/SDL.h>

// Forward declaration
class	Game;

/*
** GameState class
*/

class	GameState
{
public:
  GameState(Game *game);
  virtual ~GameState();

  virtual void	handleEvent();
  virtual void	update();
  virtual void	draw();

  virtual void	pause();
  virtual void	resume();

private:
  Game		*game;
};

#endif /* !GAMESTATE_HPP_ */
