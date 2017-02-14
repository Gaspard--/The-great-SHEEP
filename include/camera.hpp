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

  Vect<2u, double> getPosition(void) const;
  void	setPosition(const Vect<2u, double> &position);

  void	move(Vect<2u, double> &offset);

  Vect<2u, int> getFlooredCamera(void) const;

private:
  Vect<2, double> position;
};

#endif // !CAMERA_HPP_
