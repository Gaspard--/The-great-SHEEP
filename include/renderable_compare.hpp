#ifndef RENDERABLE_COMPARE_HPP_
# define RENDERABLE_COMPARE_HPP_

class Renderable;
class Display;

class RenderableCompare
{
private:
  Display *display;
public:
  RenderableCompare(Display *display);
  bool operator()(Renderable *A, Renderable *B);
};

#endif // !RENDERABLE_COMPARE_HPP_
