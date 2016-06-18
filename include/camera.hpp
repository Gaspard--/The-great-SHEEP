#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

# include "vect.hpp"

class Camera
{
public:
  Camera(void);
  ~Camera(void);

  void	setCamera(double x, double y);
  void	moveCamera(double x, double y);
  Vect<2u, double> const &getCamera(void) const;
  Vect<2u, int> const getFlooredCamera(void) const;
private:
  Vect<2, double> lookat;
};

#endif // !CAMERA_HPP_
