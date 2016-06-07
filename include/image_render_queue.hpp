#ifndef IMAGE_RENDER_QUEUE_HPP_
# define IMAGE_RENDER_QUEUE_HPP_

# include <string>
# include <string.h>
# include "render_queue.hpp"
# include "vect.hpp"

class		ImageRenderQueue:
  public	RenderQueue<float, Vect<4, float>[3]>
{
public:
  GLuint	image;
  ImageRenderQueue();
  virtual void	draw(Vect<4, float> triangle[3]);
  virtual void	render(int amount);
};

#endif // IMAGE_RENDER_QUEUE_HPP_
