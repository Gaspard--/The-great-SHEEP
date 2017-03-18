#ifndef MOVING_VECTOR_HPP
# define MOVING_VECTOR_HPP

#include <new>
#include <memory>
#include <iostream>

template<class T, size_t reserveSize = 50>
class MovingVector
{
private:
  class Deleter
  {
  public:
    void operator()(T *t)
    {
      ::operator delete(reinterpret_cast<void *>(t));
    }
  };
  std::unique_ptr<T[], Deleter>	data;
  size_t		size;
  size_t		capacity;
  
public:
  MovingVector(size_t capacity = reserveSize)
    : data(reinterpret_cast<T *>(::operator new(capacity * sizeof(T)))), size(0u), capacity(capacity)
  {
  }

  MovingVector(MovingVector<T> &other)
    : MovingVector<T>(capacity)
  {
  }

  ~MovingVector()
  {
    while (size)
      {
	data[size].~T();
	--size;
      }
  }
  
  T &operator[](size_t i)
  {
    return (data[i]);
  }
  
  T const &operator[](size_t i) const
  {
    return (data[i]);
  }

  void swap(MovingVector &other)
  {
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
  }

  void reserve(size_t capacity)
  {
    MovingVector tmp(capacity);

    while (tmp.size != size)
      tmp.move_back(std::move(data[tmp.size]));
    this->swap(tmp);
  }

  void move_back(T &&t)
  {
    if (size == capacity)
      reserve(capacity + reserveSize);
    new (&data[size])T(std::move(t));
    ++size;    
  }

  template<class... P>
  void emplace_back(P &&... ps)
  {
    if (size == capacity)
      reserve(capacity + reserveSize);
    new (&data[size])T(ps...);
    ++size;
  }

  void erase(T *t)
  {
    t->~T();
    while (t != end() - 1)
      {
	new (t)T(std::move(t[1]));
	++t;
	t->~T();
      }
    --size;
  }

  // void erase(T *t)
  // {
  //   while (t != end() - 1)
  //     {
  // 	*t = std::move(t[1]);
  // 	++t;
  //     }
  //   t->~T();
  //   --size;
  // }

  T *begin()
  {
    return &data[0];
  }

  T *end()
  {
    return &data[size];
  }
};

#endif
