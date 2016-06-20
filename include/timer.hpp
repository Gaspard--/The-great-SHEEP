#ifndef TIMER_HPP_
# define TIMER_HPP_

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>

// Forward declaration
class Game;

/*
** Class timer, used to display fps
*/
class Timer
{
public:
  // Constructor/Destructor
  Timer(Game *game);
  ~Timer();

  void		update();
  void		showFps();
  double	getFps();
  bool		getShow();
  void		toggleShow();

private:
  char		buffer[256];
  Game		*game;

  TTF_Font	*font;
  SDL_Rect	msgRect;
  SDL_Texture	*msg;
  SDL_Surface	*surfaceMessage;
  // Number of frame since the beginning
  int		frame;

  // Ticks
  Uint32	startTicks;
  Uint32	elapsedTicks;

  // Times
  double	elapsed;

  // Frame per second
  double	fps;

  bool		show;
};

#endif /* !TIMER_HPP_ */
