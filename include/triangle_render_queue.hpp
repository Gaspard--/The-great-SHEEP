#ifndef TRIANGLE_RENDER_QUEUE_HPP_
# define TRIANGLE_RENDER_QUEUE_HPP_

# include <string>
# include <string.h>
# include "render_queue.hpp"
# include "my_opengl.hpp"
# include "vect.hpp"

class		TriangleRenderQueue:
  public	RenderQueue<float, Vect<6, float>[3]>
{
public:
  TriangleRenderQueue();
  virtual void	draw(Vect<6, float> triangle[3]);
  virtual void	render(int amount);
};

#endif // TRIANGLE_RENDER_QUEUE_HPP_
