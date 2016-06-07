#include "image_render_queue.hpp"

ImageRenderQueue::ImageRenderQueue()
{
  GLchar	vertSource[] =
    "#version 130			\n" \
    "uniform vec2	camera;		\n" \
    "uniform vec2	rotation;	\n" \
    "uniform float	ratio;		\n" \
    "in vec2		pos;		\n" \
    "in vec2		coord;		\n" \
    "out vec4		vert_coord;	\n" \
    "void main()			\n" \
    "{					\n" \
    "  vec2		newpos;		\n" \
    "  vert_coord = coord;		\n" \
    "  newpos = pos - camera;		\n" \
    "  newpos = newpos * rotation.xx + newpos.yx * rotation.yy * vec2(-1, 1);\n" \
    "  newpos = newpos * vec2(ratio, 1);\n" \
    "  gl_Position = vec4(newpos, 0, 1);\n" \
    "}					\n";
  GLchar	fragSource[] =
    "#version 130				\n" \
    "in vec4		vert_coord;		\n" \
    "out vec4		frag_color;		\n" \
    "uniform sampler2D	image;			\n" \
    "void main()				\n" \
    "{						\n" \
    "  frag_color = texture(image, vert_coord);	\n" \
    "}						\n";

  glShaderProgram = my_opengl::createProgram(new GLuint[2]{
      GL_VERTEX_SHADER, GL_FRAGMENT_SHADER},
    new const GLchar*[2]{vertSource, fragSource}, 2);
  glBindVertexArray(glVAO);
  glUseProgram(glShaderProgram);
  glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(GLfloat), (void *)0);
  glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(GLfloat),
			(void *)(2 * sizeof(GLfloat)));
  glBufferData(GL_ARRAY_BUFFER, 0, (void *)0, GL_STATIC_DRAW);
}

void	ImageRenderQueue::render(int amount)
{
  glDrawArrays(GL_TRIANGLES, 0, amount);
}

void	ImageRenderQueue::draw(Vect<4, float> triangle[3])
{
  buffer->prepareCapacity(12)->noIfAdd(triangle[0].data, 4);
  buffer->noIfAdd(triangle[1].data, 4)->noIfAdd(triangle[2].data, 4);
  vertexAmount = vertexAmount + 3;
}
