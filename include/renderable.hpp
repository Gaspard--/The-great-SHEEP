#ifndef RENDERABLE_HPP_
# define RENDERABLE_HPP_

#include "vect.hpp"

class Renderable
{
public:
  Renderable(Vect<2u, double> *position, Vect<2u, double> *dimensions);
  Vect<2u, double>	*position;
  Vect<2u, double>	*dimensions;
};

#endif // !RENDERABLE_HPP_
