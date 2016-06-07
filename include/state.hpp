#ifndef STATE_HPP_
# define STATE_HPP_

#include "display.hpp"
#include "logic.hpp"
#include "input.hpp"

class	State
{
public:
  Display	*display;
  Logic		*logic;
  Input		*input;
};

#endif // STATE
