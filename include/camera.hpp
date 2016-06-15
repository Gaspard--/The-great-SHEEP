#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include "vect.hpp"

class	Camera
{
public:
  Camera();
  ~Camera();

  void	setCamera(double x, double y);
  void	moveCamera(double x, double y);
  const Vect <2, double>& getCamera(void);

private:
  Vect<2, double> lookat;
};

#endif // !CAMERA_HPP_
