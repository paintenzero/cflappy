#include "startscreen.h"

extern SDL_Rect logoClip;
extern SDL_Rect tapClip;

int startScreenCreate ()
{
    return 0;
}

void startScreenDestroy ()
{
}

void startScreenDraw (SDL_Surface *destination)
{
  SDL_Rect pos;
  //draw logo
  pos.x = (destination->w - logoClip.w)/2;
  pos.y = 100;
  SDL_BlitSurface (spritesheet, &logoClip, destination, &pos);
  //draw get ready
  pos.x = (destination->w - tapClip.w)/2;
  pos.y += logoClip.h+50;
  SDL_BlitSurface (spritesheet, &tapClip, destination, &pos);
}
