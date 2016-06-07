#ifndef COMPLEX_HPP_
# define COMPLEX_HPP_

template<class T>
class		Complex:
  public	Vect<2u, T>
{
public:
  Complex()
  {
  }

  Complex(Vect<2u, T> vec)
  {
    memcpy(this->data, vec.data, 2 * sizeof(T));
  }

  Complex(T reel, T img)
  {
    this->data[0] = reel;
    this->data[1] = img;
  }

  Complex<T>	operator*(Complex<T> other)
  {
    return (Complex(other.data[0] * this->data[0] - other.data[1] * this->data[1],
		    other.data[0] * this->data[1] + other.data[1] * this->data[0]));
  }

  Complex<T>	operator/(Complex<T> other)
  {
    return (*this * Complex(new float[2]{other.data[0], -other.data[1]})
	    / (other.data[0] * other.data[0] + other.data[1] * other.data[1]));
  }

  Complex<T>	operator+(Complex<T> other)
  {
    return (static_cast<Complex<T>>(Vect<2u, T>::operator+(other)));
  }

  Complex<T>	operator-(Complex<T> other)
  {
    return (static_cast<Complex<T>>(Vect<2u, T>::operator-(other)));
  }

  Complex<T>	operator*(T other)
  {
    return (static_cast<Complex<T>>(Vect<2u, T>::operator*(other)));
  }

  Complex<T>	operator/(T other)
  {
    return (static_cast<Complex<T>>(Vect<2u, T>::operator/(other)));
  }

  Complex<T>	operator=(Vect<2, T> other)
  {
    return (static_cast<Complex<T>>(other));
  }
};

#endif // COMPLEX_HPP_
