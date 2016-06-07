#include "triangle_render_queue.hpp"

TriangleRenderQueue::TriangleRenderQueue()
{
  GLchar	vertSource[] =
    "#version 130			\n" \
    "uniform vec2	camera;		\n" \
    "uniform vec2	rotation;	\n" \
    "uniform float	ratio;		\n" \
    "in vec2		pos;		\n" \
    "in vec4		color;		\n" \
    "out vec4		vert_color;	\n" \
    "void main()			\n" \
    "{					\n" \
    "  vec2		newpos;		\n" \
    "  vert_color = color;		\n" \
    "  newpos = pos - camera;		\n" \
    "  newpos = newpos * rotation.xx + newpos.yx * rotation.yy * vec2(-1, 1);\n" \
    "  newpos = newpos * vec2(ratio, 1);\n" \
    "  gl_Position = vec4(newpos, 0, 1);\n" \
    "}					\n";
  GLchar	fragSource[] =
    "#version 130		\n" \
    "in vec4	vert_color;	\n" \
    "out vec4	frag_color;	\n" \
    "void main()		\n" \
    "{				\n" \
    "  frag_color = vert_color;	\n" \
    "}				\n";

  glShaderProgram = my_opengl::createProgram(new GLuint[2]{
      GL_VERTEX_SHADER, GL_FRAGMENT_SHADER},
    new const GLchar*[2]{vertSource, fragSource}, 2);
  glBindVertexArray(glVAO);
  glUseProgram(glShaderProgram);
  glBindBuffer(GL_ARRAY_BUFFER, glBuffer);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 2, GL_FLOAT, false, 6 * sizeof(GLfloat), (void *)0);
  glVertexAttribPointer(1, 4, GL_FLOAT, false, 6 * sizeof(GLfloat),
			(void *)(2 * sizeof(GLfloat)));
  glBufferData(GL_ARRAY_BUFFER, 0, (void *)0, GL_STATIC_DRAW);
}

void	TriangleRenderQueue::render(int amount)
{
  glDrawArrays(GL_TRIANGLES, 0, amount);
}

void	TriangleRenderQueue::draw(Vect<6, float> triangle[3])
{
  buffer->prepareCapacity(18)->noIfAdd(triangle[0].data, 6);
  buffer->noIfAdd(triangle[1].data, 6)->noIfAdd(triangle[2].data, 6);
  vertexAmount = vertexAmount + 3;
}
