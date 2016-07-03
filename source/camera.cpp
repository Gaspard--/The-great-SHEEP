#include "top_header.hpp"
#include "camera.hpp"
#include <iostream>

Camera::Camera(void)
{
  position = Vect<2, double>(TILE_DIM / 2, TILE_DIM / 2);

  //1st int : 0 = north/south, 1 = east/west
  //2nd int : 0 = top/down, 1 = down/top
  angle = Vect<2, int>(0, 0);
}

Camera::~Camera(void)
{
}

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
  Vect<2, int> angle = getAngle();

  if (angle[0])
    {
      double tmp = offset[0];

      offset[0] = -offset[1];
      offset[1] = tmp;
    }

  if (angle[1])
    {
      offset[0] = -offset[0];
      offset[1] = -offset[1];
    }

  position += offset;
}

Vect<2u, int> Camera::getAngle(void) const
{
  return (angle);
}

void Camera::setAngle(const Vect<2u, int>& newAngle)
{
  angle ^= newAngle;
}

Vect<2u, int> Camera::getFlooredCamera(void) const
{
  Vect<2, int> offset(position.x() < 0 && (int)position.x() != position.x(),
                      position.y() < 0 && (int)position.y() != position.y());

  return Vect<2u, int>(position) + offset;
}
