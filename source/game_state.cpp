#include "game_state.hpp"

GameState::GameState()
{
  terrain = terrain_generator::generateTerrain1(3);
  display = new GameDisplay(this);
  logic = new GameLogic(this);
}
