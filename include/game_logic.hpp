#ifndef GAME_LOGIC_HPP_
# define GAME_LOGIC_HPP_

# include "game_state.hpp"

class	GameState;

class	GameLogic
{
public:
  GameState	*game;

  GameLogic(GameState *game);
  void		tick();
};

#endif // GAME_LOGIC_HPP_
