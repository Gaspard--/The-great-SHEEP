#include "top_header.hpp"
#include "camera.hpp"

Camera::Camera()
{
  lookat.data[0] = TILE_WIDTH / 2;
  lookat.data[1] = TILE_HEIGHT / 2;
}

Camera::~Camera()
{
}

const Vect<2, double>& Camera::getCamera()
{
  return (lookat);
}

void Camera::setCamera(double x, double y)
{
  lookat.data[0] = x;
  lookat.data[1] = y;
}

void Camera::moveCamera(double x, double y)
{
  lookat.data[0] += x;
  lookat.data[1] += y;
}
