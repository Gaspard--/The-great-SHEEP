#include "top_header.hpp"
#include "camera.hpp"
#include <iostream>

Camera::Camera()
{
  window_camera.x = 0;
  window_camera.y = 0;
  window_camera.w = WINDOW_WIDTH;
  window_camera.h = WINDOW_HEIGHT;
  calcAbstractCamera();
  abstract_camera.w = TILE_WIDTH;
  abstract_camera.h = TILE_HEIGHT;
}

Camera::~Camera()
{
}

void	Camera::calcAbstractCamera()
{
  abstract_camera.x = window_camera.x / 60;
  abstract_camera.y = window_camera.y / 30;
}

const SDL_Rect& Camera::getAbstractCamera()
{
  return (abstract_camera);
}

const SDL_Rect& Camera::getWindowCamera()
{
  return (window_camera);
}

void    Camera::setCamera(int x, int y)
{
  window_camera.x = x;
  window_camera.y = y;
  calcAbstractCamera();
}

void    Camera::moveCamera(int x, int y)
{
  window_camera.x += x;
  window_camera.y += y;
  calcAbstractCamera();
}
