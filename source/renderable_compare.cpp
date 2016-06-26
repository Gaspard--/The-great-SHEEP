#include "renderable_compare.hpp"
#include "display.hpp"
#include "renderable.hpp"

RenderableCompare::RenderableCompare(Display *display) : display(display)
{
}

bool RenderableCompare::operator()(Renderable *A, Renderable *B)
{
  return (display->fullIsometrize(*A->position)[1] < display->fullIsometrize(*B->position)[1]);
}
