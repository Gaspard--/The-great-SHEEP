#include "camera.hpp"
#include <iostream>

Vect<2u, double> Camera::getPosition(void) const
{
  return (position);
}

void Camera::setPosition(const Vect<2u, double>& newPosition)
{
  position = newPosition;
}

void Camera::move(Vect<2, double>& offset)
{
  position += offset;
}

Vect<2u, int> Camera::getFlooredCamera(void) const
{
  Vect<2, int> offset(position.x() < 0 && (int)position.x() != position.x(),
                      position.y() < 0 && (int)position.y() != position.y());

  return Vect<2u, int>(position) + offset;
}
