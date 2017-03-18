#ifndef FOLLOWABLE_VECTOR_HPP
# define FOLLOWABLE_VECTOR_HPP

#include "moving_vector.hpp"
#include "follow.hpp"

template<class T, size_t step = 50>
class FollowableVector : private MovingVector<Followable<T>, step>
{
 public:
  using MovingVector<Followable<T>, step>::MovingVector;

  using MovingVector<Followable<T>, step>::begin;
  using MovingVector<Followable<T>, step>::end;
  using MovingVector<Followable<T>, step>::operator [];

  template<class... Params>
  void operator()(Follower<T> &follower, Params &&... params)
  {
    this->emplace_back(T{params...}, follower,
		       [this](Followable<T> &r)
		       {
			 this->erase(&r);
		       });
  }

  
};

#endif
