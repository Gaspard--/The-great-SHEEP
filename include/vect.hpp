#ifndef VECT_HPP_
# define VECT_HPP_

# include <type_traits>

template <unsigned int dim, class T>
class Vect
{
private:
  T data[dim];

public:
  T& operator[](unsigned int index)
  {
    return (data[index]);
  }

  T const operator[](unsigned int index) const
  {
    return (data[index]);
  }

  Vect(void)
  {
  }

  Vect(Vect<dim, T> const &other)
  {
    unsigned int i;

    i = 0;
    while (i < dim)
      {
	data[i] = other[i];
	i = i + 1;
      }
  }

  template<class U>
  Vect(Vect<dim, U> const &other)
  {
    unsigned int i;

    i = 0;
    while (i < dim)
      {
	data[i] = static_cast<T>(other[i]);
	i = i + 1;
      }
  }

  template<unsigned int dim2, class U, class V>
  Vect(Vect<dim2, U>& other, Vect<dim - dim2, V>& other2)
  {
    unsigned int i;

    i = 0;
    while (i < dim2)
      {
	data[i] = static_cast<T>(other[i]);
	i = i + 1;
      }
    while (i < dim)
      {
	data[i] = static_cast<T>(other2[i - dim2]);
	i = i + 1;
      }
  }

  template<class... U, class V>
  Vect(V first, U... more) : Vect(more...)
  {
    data[dim - sizeof...(more) - 1] = static_cast<T>(first);
  }

  Vect<dim, T> operator+(Vect<dim, T> const &other)
  {
    Vect<dim, T> result;
    unsigned int i;

    i = 0;
    while (i < dim)
      {
	result[i] = other[i] + data[i];
	i = i + 1;
      }
    return (result);
  }

  Vect<dim, T> operator-(Vect<dim, T> const &other) const
  {
    Vect<dim, T> result;
    unsigned int i;

    i = 0;
    while (i < dim)
      {
	result[i] = data[i] - other[i];
	i = i + 1;
      }
    return (result);
  }

  Vect<dim, T> operator-(void) const
  {
    Vect<dim, T> result;
    unsigned int i;

    i = 0;
    while (i < dim)
      {
	result[i] = -data[i];
	i = i + 1;
      }
    return (result);
  }

  Vect<dim, T> operator*(T const& other) const
  {
    Vect<dim, T> result;
    unsigned int i;

    i = 0;
    while (i < dim)
      {
	result[i] = data[i] * other;
	i = i + 1;
      }
    return (result);
  }

  Vect<dim, T> operator*(Vect<dim, T> const& other) const
  {
    Vect<dim, T> result;
    unsigned int i;

    i = 0;
    while (i < dim)
      {
	result[i] = data[i] * other[i];
	i = i + 1;
      }
    return (result);
  }

  Vect<dim, T> operator/(T const& other) const
  {
    Vect<dim, T>	result;
    unsigned int	i;

    i = 0;
    while (i < dim)
      {
	result[i] = data[i] / other;
	i = i + 1;
      }
    return (result);
  }

  T sum(void) const
  {
    unsigned int	i;
    T			result;

    result = 0u;
    i = 0u;
    while (i < dim)
      {
	result = result + data[i];
	i = i + 1u;
      }
    return (result);
  }

  T scalar(Vect<dim, T>& other) const
  {
    return ((*this * other).sum());
  }

  template<unsigned int _dim = dim, typename std::enable_if<(dim > 0)>::type* = nullptr>
  T x()
  {
    return (data[0]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(dim > 1)>::type* = nullptr>
  T y() const
  {
    return (data[1]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 2)>::type* = nullptr>
  T z() const
  {
    return (data[2]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 3)>::type* = nullptr>
  T w() const
  {
    return (data[3]);
  }
};

#endif // VECT_HPP_
