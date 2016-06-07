#ifndef GAME_STATE_HPP_
# define GAME_STATE_HPP_

# include "terrain_generator.hpp"
# include "terrain.hpp"
# include "state.hpp"
# include "game_logic.hpp"
# include "game_display.hpp"

class		GameDisplay;
class		GameLogic;

class		GameState:
  public	State
{
public:
  Terrain	*terrain;
  GameState();
};

#endif // GAME_STATE_HPP_
