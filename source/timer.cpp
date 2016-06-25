#include <iostream>
#include <stdio.h>
#include "game.hpp"
#include "timer.hpp"

Timer::Timer(Game *game) : game(game)
{
  if (TTF_Init() == -1)
    std::cout << TTF_GetError() << std::endl;
  font = TTF_OpenFont("fonts/OpenSans-Semibold.ttf", 50);
  fps = 0;
  frame = 0;
  old = SDL_GetTicks();
  show = false;
  surfaceMessage = NULL;
  msg = NULL;
  msgRect.x = 10;
  msgRect.y = 0;
  msgRect.w = 50;
  msgRect.h = 50;
}

Timer::~Timer()
{
  TTF_CloseFont(font);
  TTF_Quit();
}

void	Timer::update()
{
  if (SDL_GetTicks() - old < 1000)
    {
      frame += 1;
    }
  else
    {
      fps = frame;
      frame = 0;
      old = SDL_GetTicks();
    }
}

void	Timer::showFps()
{
  sprintf(buffer, "%d", fps);
  surfaceMessage = TTF_RenderText_Solid(font, buffer, {125, 125, 125, 255});
  if (!surfaceMessage)
    std::cout << TTF_GetError() << std::endl;
  msg = SDL_CreateTextureFromSurface(game->getRenderer(), surfaceMessage);
  SDL_RenderCopy(game->getRenderer(), msg, NULL, &msgRect);
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(msg);
  surfaceMessage = NULL;
  msg = NULL;
}

double	Timer::getFps()
{
  return (fps);
}

void	Timer::toggleShow()
{
  show = (show) ? false : true;
}

bool	Timer::getShow()
{
  return (show);
}
