#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>

class	Camera
{
public:
  Camera();
  ~Camera();

  void	setCamera(int x, int y);
  void	moveCamera(int x, int y);
  const SDL_Rect& getAbstractCamera(void);
  const SDL_Rect& getWindowCamera(void);
  void	calcAbstractCamera();

private:
  SDL_Rect abstract_camera;
  SDL_Rect window_camera;
};

#endif // !CAMERA_HPP_
