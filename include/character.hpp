#ifndef CHARACTER_HPP_
# define CHARACTER_HPP_

namespace display
{
      enum character_names
	{
	  CHARACTER_MAIN,
	  CHARACTER_DRAGOON,
	  CHARACTER_TROLL,
	  CHARACTER_SPIDER,
	  CHARACTER_HARPY,
	  CHARACTER_MAX
	};
};

struct  Character
{
  int	x;
  int	y;
  int   type;
};

#endif // !CHARACTER_HPP_
