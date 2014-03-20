#include "readyscreen.h"

extern SDL_Rect readyClip;
extern SDL_Rect largeFontClip[10];
unsigned int counter;
unsigned int startTime;

int readyScreenCreate ()
{
  return 0;
}

void readyScreenDestroy ()
{
}

void readyScreenDraw (SDL_Surface *destination)
{
  SDL_Rect pos;
  //draw logo
  pos.x = (destination->w - readyClip.w)/2;
  pos.y = 100;
  SDL_BlitSurface (spritesheet, &readyClip, destination, &pos);
  //draw get ready
  pos.x = (destination->w - largeFontClip[counter].w)/2;
  pos.y += readyClip.h+50;
  SDL_BlitSurface (spritesheet, &largeFontClip[counter], destination, &pos);
}

void readyScreenReset ()
{
  startTime = SDL_GetTicks ();
  counter = 3;
}

int readyScreenStep (unsigned int dt)
{
  unsigned int curTime = SDL_GetTicks ();
  while ((curTime-startTime)>=1000){
    --counter;
    startTime += 1000;
  }
  return counter;
}
