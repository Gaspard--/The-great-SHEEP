#ifndef VECT_HPP_
# define VECT_HPP_

# include <iostream>
# include <array>

template <unsigned int dim, class T>
class Vect
{
public:
  T		data[dim];

  Vect()
  {
  }

  Vect(const Vect<dim, T>& other)
  {
    unsigned int	i;

    i = 0;
    while (i < dim)
      {
	data[i] = other.data[i];
	i = i + 1;
      }
  }

  template<class U>
  Vect(const Vect<dim, U>& other)
  {
    unsigned int	i;

    i = 0;
    while (i < dim)
      {
	data[i] = static_cast<T>(other.data[i]);
	i = i + 1;
      }
  }

  template<unsigned int dim2, class U, class V>
  Vect(Vect<dim2, U>& other, Vect<dim - dim2, V>& other2)
  {
    unsigned int	i;

    i = 0;
    while (i < dim2)
      {
	data[i] = static_cast<T>(other.data[i]);
	i = i + 1;
      }
    while (i < dim)
      {
	data[i] = static_cast<T>(other2.data[i - dim2]);
	i = i + 1;
      }
  }

  // Vect(T t[dim]) : data(t)
  // {
  // }

  template<class... U, class V>
  Vect(V first, U... more) : Vect(more...)
  {
    data[dim - sizeof...(more) - 1] = static_cast<T>(first);
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
