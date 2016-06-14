#ifndef OBJECT_HPP_
# define OBJECT_HPP_

namespace display
{
  enum object_names
    {
      OBJECT_HOUSE,
      OBJECT_TREE,
      OBJECT_TREE2,
      OBJECT_CASTLE,
      OBJECT_WALL,
      OBJECT_MAX
    };
};

struct  Object
{
  int   type;
  int	x;
  int	y;
  int	iso_x;
  int	iso_y;
};

#endif // !OBJECT_HPP_
