#ifndef __READYSCREEN_H__
#define __READYSCREEN_H__

#include "sdlutils.h"

int readyScreenCreate ();
void readyScreenDestroy ();
void readyScreenDraw (SDL_Surface *destination);

void readyScreenReset ();
int readyScreenStep (unsigned int dt);

#endif
