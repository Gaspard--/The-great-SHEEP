#include "top_header.hpp"
#include "camera.hpp"

Camera::Camera(void)
{
  lookat[0] = TILE_WIDTH / 2;
  lookat[1] = TILE_HEIGHT / 2;
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
