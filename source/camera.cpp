#include "top_header.hpp"
#include "camera.hpp"

#include <iostream>

Camera::Camera(void)
{
  position = Vect<2, double>(TILE_DIM / 2, TILE_DIM / 2);
  angle = Vect<2, int>(0, 0);
}

Camera::~Camera(void)
{
}


Vect<2u, double> Camera::getPosition(void) const
{
  return (position);
}

void Camera::setPosition(const Vect<2u, double> &newPosition)
{
  position = newPosition;
}

void Camera::move(const Vect<2, double> &offset)
{
  position += offset;
}


Vect<2u, int> Camera::getAngle(void) const
{
  return (angle);
}

void Camera::setAngle(const Vect<2u, int> &newAngle)
{
  angle ^= newAngle;
}


Vect<2u, int> Camera::getFlooredCamera(void) const
{
  Vect<2, int> offset(position.x() < 0 && (int)position.x() != position.x(),
                      position.y() < 0 && (int)position.y() != position.y());

  return Vect<2u, int>(position) + offset;
}
