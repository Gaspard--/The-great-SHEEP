#ifndef GAMESTATE_HPP_
# define GAMESTATE_HPP_

# include <string>
# include <SDL2/SDL.h>

// Forward declaration
class	Game;

/*
** GameState class
*/
class	IGameState
{
public:
  // Constructor/Destructor
  virtual ~IGameState() {};
  virtual void	init(Game *game) = 0;
  virtual void	destroy() = 0;

  // Write your Event handler in this function
  virtual void	handleEvent() = 0;

  // Called before draw()
  virtual void	update() = 0;

  // Render in this function
  virtual void	draw() = 0;

  // Useless for now
  virtual void	pause() = 0;
  virtual void	resume() = 0;
};

#endif /* !GAMESTATE_HPP_ */
