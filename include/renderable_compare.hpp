#ifndef RENDERABLE_COMPARE_HPP_
# define RENDERABLE_COMPARE_HPP_

class Renderable;

class RenderableCompare
{
public:
  bool operator()(Renderable *A, Renderable *B);
};

#endif // !RENDERABLE_COMPARE_HPP_
