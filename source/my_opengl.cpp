#include "my_opengl.hpp"
#include <iostream>

void		my_opengl::shaderError(GLenum shadertype, GLuint shader)
{
  GLint		len;
  GLchar	*log;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  std::cout << "Compilation failed for ";
  std::cout << ((shadertype == GL_VERTEX_SHADER) ?
		"vertex" : (shadertype == GL_FRAGMENT_SHADER) ?
		"fragment" : "unknown (fix this in gl_helpers!)");
  std::cout << " shader:" << std::endl;
  log = new GLchar[len];
  glGetShaderInfoLog(shader, len, NULL, log);
  std::cout << log << std::endl;
  exit(1);
}

void		my_opengl::programError(GLuint program)
{
  GLint		len;
  GLchar	*log;

  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
  log = new GLchar[len];
  glGetProgramInfoLog(program, len, NULL, log);
  std::cout << "link failure:" << std::endl;
  std::cout << log << std::endl;
  exit(1);
}

Shader		my_opengl::createShader(GLenum shadertype, const GLchar *src)
{
  Shader	shader;
  GLint		status;

  shader = glCreateShader(shadertype);
  glShaderSource(shader, 1, &src, 0);
  glCompileShader(shader);

  status = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
    shaderError(shadertype, shader);
  return (shader);
}

Program		my_opengl::createProgram(const Shader *shaders, int count)
{
  Program	program;
  GLint		status;
  int		i;

  program = glCreateProgram();
  i = 0;
  while (i < count)
    {
      glAttachShader(program, shaders[i]);
      i = i + 1;
    }
  glLinkProgram(program);
  i = 0;
  while (i < count)
    {
      glDetachShader(program, shaders[i]);
      i = i + 1;
    }

  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status == GL_FALSE)
    programError(program);
  return (program);
}

Program		my_opengl::createProgram(const GLenum *shader_types,
					 const GLchar **shader_srcs,
					 int count)
{
  int		i;
  Shader	*shaders;

  shaders = new GLuint[count];
  i = 0;
  while (i < count)
    {
      shaders[i] = createShader(shader_types[i], shader_srcs[i]);
      i = i + 1;
    }
  return (createProgram(shaders, count));
}
