#ifndef MY_OPENGL_HPP_
# define MY_OPENGL_HPP_

# include "GL/gl3w.h"
# include <GLFW/glfw3.h>


typedef GLuint Shader;
typedef GLuint Program;

namespace	my_opengl
{
  void		shaderError(GLenum shadertype, GLuint shader);
  GLuint	createShader(GLenum shadertype, const GLchar *src);
  void		programError(GLuint program);
  GLuint	createProgram(const GLenum *shaders, int count);
  GLuint	createProgram(const GLenum *shader_types,
                              const GLchar **shader_srcs,
                              int count);
};

#endif // MY_OPENGL_HPP_
