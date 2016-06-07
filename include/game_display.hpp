#ifndef GAME_DISPLAY_HPP_
# define GAME_DISPLAY_HPP_

# include "display.hpp"
# include "triangle_render_queue.hpp"
# include "my_opengl.hpp"
# include "render_queue.hpp"
# include "game_state.hpp"
# include "complex.hpp"

class	GameState;

class			GameDisplay:
  public		Display
{
private:
  Complex<float>	*camera;
  Complex<float>	*rotation;
  GameState		*game;

public:
  TriangleRenderQueue	triangleRenderQueue;

  GameDisplay(GameState *game);
  virtual void		render();
  void			drawTile(Complex<int> pos);
  void			drawTerrain();

  template<class StorageType, class DrawType>
  void	renderRenderQueue(RenderQueue<StorageType, DrawType> *renderQueue)
  {
    if (renderQueue->vertexAmount)
      {
	glBindVertexArray(renderQueue->glVAO);
	glUseProgram(renderQueue->glShaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, renderQueue->glBuffer);
	glBufferData(GL_ARRAY_BUFFER,
		     renderQueue->buffer->data_size * sizeof(StorageType),
		     renderQueue->buffer->data, GL_STATIC_DRAW);
	glUniform2f(glGetUniformLocation(renderQueue->glShaderProgram, "camera"),
		    camera->data[0], camera->data[1]);
	glUniform1f(glGetUniformLocation(renderQueue->glShaderProgram, "ratio"),
		    HEIGHT / (float) WIDTH);
	glUniform2f(glGetUniformLocation(renderQueue->glShaderProgram, "rotation"),
		    rotation->data[0], rotation->data[1]);
	//	glDrawArrays(GL_TRIANGLES, 0, renderQueue->vertexAmount);
	renderQueue->render(renderQueue->vertexAmount);
      }
  }
};

#endif // GAME_DISPLAY_HPP_
