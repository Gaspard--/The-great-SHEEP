#ifndef FOLLOW_HPP
# define FOLLOW_HPP

# include <functional>
# include <new>

template<class T>
struct Followable
{
public:


  class Follower
  {
  public:
    Followable<T>	*followable;

    Follower()
      : followable(nullptr)
    {
    }

    ~Follower()
    {
      followable->deleter(*followable);
    }

    Follower(Follower const &) = delete;

    Followable<T> &operator->()
    {
      return *followable;
    }

    Followable<T> const &operator->() const
    {
      return *followable;
    }

    T &operator*()
    {
      return **followable;
    }

    T const &operator*() const
    {
      return **followable;
    }
  };
  friend class Follower;
  T     	val;
  Follower	&follower;
  // Not optimised but far more convenient.
  std::function<void(Followable<T> &)>	deleter;

  Followable(T const &val, Follower &follower, std::function<void(Followable<T> &)> deleter)
    : val(val), follower(follower), deleter(deleter)
  {
    follower.followable = this;
  }
  
  Followable(Followable<T> &f) = delete;

  Followable(Followable<T> &&f)
    : Followable<T>(f.val, f.follower, f.deleter)
  {
  }

  Followable<T> &operator=(Followable<T> &&f)
  {
    new (this)Followable<T>(std::move(f));
    return *this;
  }

  T *operator->()
  {
    return &val;
  }

  T const *operator->() const
  {
    return &val;
  }

  T &operator*()
  {
    return val;
  }

  T const &operator*() const
  {
    return val;
  }
};

template<class T>
using Follower = typename Followable<T>::Follower;

#endif
