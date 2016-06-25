#include "renderable_compare.hpp"
#include "renderable.hpp"

bool RenderableCompare::operator()(Renderable *A, Renderable *B)
{
  return (A->front() < B->front());
}
