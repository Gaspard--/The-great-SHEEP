#ifndef RENDER_QUEUE_HPP_
# define RENDER_QUEUE_HPP_

# include <vector>
# include "buffer.hpp"
# include "my_opengl.hpp"

template <class StorageType, class DrawType>
class			RenderQueue
{
public:
  GLuint		glVAO;
  GLuint		glShaderProgram;
  GLuint		glBuffer;
  Buffer<StorageType>	*buffer;
  unsigned int		vertexAmount;

  RenderQueue()
  {
    buffer = new Buffer<StorageType>();
    glGenVertexArrays(1, &glVAO);
    glGenBuffers(1, &glBuffer);
    vertexAmount = 0;
  }

  void		reset()
  {
    vertexAmount = 0;
    delete buffer;
    buffer = new Buffer<StorageType>();
  }

  virtual void	draw(DrawType object) = 0;
  virtual void	render(int amount) = 0;
};

#endif // RENDER_QUEUE_HPP_
