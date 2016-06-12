#ifndef VECT_HPP_
# define VECT_HPP_

# include <stdarg.h>
# include <iostream>

template <unsigned int dim, class T>
class Vect
{
public:
  T		data[dim];

  Vect()
  {
  }

  template<class U>
  Vect(Vect<dim, U> other)
  {
    int	i;

    i = 0;
    while (i < dim)
      {
	data[i] = static_cast<U>(other.data[i]);
	i = i + 1;
      }
  }

  Vect(T t[dim])
  {
    int	i;

    i = 0;
    while (i < dim)
      {
	data[i] = t[i];
	i = i + 1;
      }
  }
  
  Vect(T first, ...)
  {
    unsigned int	i;
    va_list		args;

    va_start(args, first);
    i = 0;
    while (i < dim)
      {
	data[i] = va_arg(args, T);
	i = i + 1;
      }
    va_end(args);
  }

  Vect<dim, T>		operator+(const Vect<dim, T>& other)
  {
    Vect<dim, T>	result;
    unsigned int	i;

    i = 0;
    while (i < dim)
      {
	result.data[i] = other.data[i] + data[i];
	i = i + 1;
      }
    return (result);
  }

  Vect<dim, T>		operator-(const Vect<dim, T>& other)
  {
    Vect<dim, T>	result;
    unsigned int	i;

    i = 0;
    while (i < dim)
      {
	result.data[i] = -other.data[i] + data[i];
	i = i + 1;
      }
    return (result);
  }

  Vect<dim, T>		operator-()
  {
    Vect<dim, T>	result;
    unsigned int	i;

    i = 0;
    while (i < dim)
      {
	result.data[i] = -data[i];
	i = i + 1;
      }
    return (result);
  }

  Vect<dim, T>		operator*(const T& other)
  {
    Vect<dim, T>	result;
    unsigned int	i;

    i = 0;
    while (i < dim)
      {
	result.data[i] = data[i] * other;
	i = i + 1;
      }
    return (result);
  }

  Vect<dim, T>		operator/(const T& other)
  {
    Vect<dim, T>	result;
    unsigned int	i;

    i = 0;
    while (i < dim)
      {
	result.data[i] = data[i] / other;
	i = i + 1;
      }
    return (result);
  }

  T			operator[](unsigned int index)
  {
    return (data[index]);
  }
};

#endif // VECT_HPP_
