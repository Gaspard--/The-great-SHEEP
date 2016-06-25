#include "top_header.hpp"
#include "camera.hpp"

#include <iostream>

Camera::Camera(void)
{
  lookat = Vect<2, double>(TILE_DIM / 2, TILE_DIM / 2);
  angle = Vect<2, int>(0, 0);
}

Camera::~Camera(void)
{
}

Vect<2u, int> const Camera::getFlooredCamera(void) const
{
  return (Vect<2u, int>(lookat) + Vect<2u, int>(lookat[0] < 0 && (int)lookat[0] != lookat[0],
						lookat[1] < 0 && (int)lookat[1] != lookat[1]));
}

Vect<2u, double> const &Camera::getCamera(void) const
{
  return (lookat);
}

Vect<2u, int> const &Camera::getAngle(void) const
{
  return (angle);
}

void Camera::changeAngle(int x, int y)
{
  angle ^= Vect<2, int>(x, y);
}

void Camera::setCamera(double x, double y)
{
  lookat[0] = x;
  lookat[1] = y;
}

void Camera::moveCamera(double x, double y)
{
  lookat[0] += x;
  lookat[1] += y;
}
