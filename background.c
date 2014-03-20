#include "background.h"
#include <math.h>

const float scrollSpeed = 120; //speed background scrolls

static float offsetX = 0;

extern SDL_Rect lightBackgroundClip;
extern SDL_Rect darkBackgroundClip;
SDL_Rect *currentTypeClip;

int backgroundCreate (BackgroundType type)
{
  if (type==light)
     currentTypeClip = &lightBackgroundClip;
  else
      currentTypeClip = &darkBackgroundClip;
  return 0;
}

void backgroundDestroy ()
{
}

void backgroundLogicStep (unsigned int dt)
{
  offsetX -= scrollSpeed*(float)dt/1000.0f;
  if (-offsetX>(*currentTypeClip).w)
  {
    offsetX = 0;
  }
}

void backgroundDraw (SDL_Surface *destination)
{
  SDL_Rect offset;
  short int anOffset = floor (offsetX);
  offset.y = (destination->h - (*currentTypeClip).h);
  while (anOffset<destination->w)
  {
    offset.x = anOffset;
    SDL_BlitSurface (spritesheet, currentTypeClip, destination, &offset);
    anOffset += (*currentTypeClip).w;
  }
}
