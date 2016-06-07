#include "my_opengl.hpp"
#include "state.hpp"
#include "game_state.hpp"
#include <iostream>

int		main()
{
  GLFWwindow	*window;
  State		*state;

  // Initialize the library
  if (!glfwInit())
    return (-1);
  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return (-1);
    }
  // Make the window's context current
  glfwMakeContextCurrent(window);
  if (gl3wInit())
    {
      std::cerr << "failed to initialize OpenGL" << std::endl;
      return -1;
    }
  if (!gl3wIsSupported(3, 0))
    {
      std::cerr << "OpenGL 3.0 not supported" << std::endl;
      return -1;
    }
  //create our gamestate
  state = new GameState();
  state->display->WIDTH = 1920;
  state->display->HEIGHT = 1080;

  // Loop until the user closes the window
  while (!glfwWindowShouldClose(window))
    {
      // update logic
      state->logic->tick();
      // render
      state->display->render();
      // Swap front and back buffers
      glfwSwapBuffers(window);
      // Poll for and process events
      glfwPollEvents();
    }
  glfwTerminate();
  return (0);
}
