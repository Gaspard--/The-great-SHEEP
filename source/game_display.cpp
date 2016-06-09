#include "game_display.hpp"
#include <string>
#include <iostream>
#include <string>
#define abs(a) (((a) > 0) ? (a) : -(a))

GameDisplay::GameDisplay(GameState *game)
{
  this->game = game;
  camera = new Complex<float>(new float[2]{30.0f, 30.0f});
  rotation = new Complex<float>(new float[2]{0.05f, 0.05f});
}

void			GameDisplay::drawTile(Complex<int> pos)
{
  Complex<float>	asFloat;

  asFloat = static_cast<Complex<float>>(pos);
  if (game->terrain->getTile(pos.data[0], pos.data[1])->isSolid())
    {
      triangleRenderQueue.draw(new Vect<6, float>[3]{
	  new float[6]{asFloat.data[0], asFloat.data[1], 1.0f, 0.0f, 1.0f, 1.0f},
	    new float[6]{asFloat.data[0] + 1.0f, asFloat.data[1], 1.0f, 1.0f, 0.0f, 1.0f},
	      new float[6]{asFloat.data[0], asFloat.data[1] + 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}});
      triangleRenderQueue.draw(new Vect<6, float>[3]{
	  new float[6]{asFloat.data[0] + 1.0f, asFloat.data[1], 1.0f, 1.0f, 0.0f, 1.0f},
	    new float[6]{asFloat.data[0], asFloat.data[1] + 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
	      new float[6]{asFloat.data[0] + 1.0f, asFloat.data[1] + 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}});
    }
}

void			GameDisplay::drawTerrain()
{
  Complex<float>	up;
  Complex<float>	reverse;
  Complex<float>	botleft;
  Complex<float>	topleft;
  Complex<float>	campos;
  Complex<int>		minvec;
  Complex<int>		maxvec;
  Complex<int>		ivec;
  Complex<int>		center;
  int			i;

  reverse = Complex<float>(new float[2]{1.0f, 0.0f}) / *rotation;
  up = reverse * Complex<float>(new float[2]{0.0f, 1.0f}) * (HEIGHT / (float) WIDTH);
  botleft = (reverse + up) * 2.0f;
  topleft = (reverse - up) * 2.0f;
  i = 0;
  while (i < 2)
    {
      minvec.data[i] = std::min(-abs(botleft.data[i]), -abs(topleft.data[i]));
      maxvec.data[i] = std::max(abs(botleft.data[i]), abs(topleft.data[i]));
      i = i + 1;
    }
  center = static_cast<Complex<int>>(*camera);
  ivec.data[0] = minvec.data[0];
  while (ivec.data[0] <= maxvec.data[0])
    {
      ivec.data[1] = minvec.data[1];
      while (ivec.data[1] <= maxvec.data[1])
	{
	  campos = static_cast<Complex<float>>(ivec) * *rotation;
	  if (campos.data[0] > -2.1 && campos.data[0] < 2.1
	      && campos.data[1] > -(2.1 * HEIGHT) / WIDTH && campos.data[1] < (2.1 * HEIGHT) / WIDTH)
	    {
	      drawTile(ivec + center);
	    }
	  ivec.data[1] = ivec.data[1] + 1;
	}
      ivec.data[0] = ivec.data[0] + 1;
    }
}

void	GameDisplay::render()
{
  triangleRenderQueue.reset();
  drawTerrain();
  triangleRenderQueue.draw(new Vect<6, float>[3]{
      Vect<6, float>(new float[6]{-0.01f, -0.1f, 1.0f, 0.0f, 0.0f, 1.0f}),
	new float[6]{0.01f, -0.1f, 1.0f, 0.0f, 0.0f, 1.0f},
	  new float[6]{0.0f, 0.1f, 0.0f, 0.0f, 1.0f, 1.0f}
    });
  *rotation = *rotation * Complex<float>(new float[2]{0.9999f, 0.01f});
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  renderRenderQueue(&triangleRenderQueue);
}
