#ifndef GAME_LOGIC_HPP_
# define GAME_LOGIC_HPP_

# include "logic.hpp"
# include "game_state.hpp"

class	GameState;

class	GameLogic:
  public Logic
{
public:
  GameState	*game;
  GameLogic(GameState *game);
  virtual void	tick();
};

#endif // GAME_LOGIC_HPP_
