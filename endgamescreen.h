#ifndef __ENDGAMESCREEN_H__
#define __ENDGAMESCREEN_H__

#include "sdlutils.h"

int endScreenCreate ();
void endScreenDestroy ();

/**
 * Sets round results
 */
void endScreenShowResult (unsigned int score, unsigned int most, unsigned int medal);
/**
 * Draws round result on a screen
 * @param destination surface to draw to
 */
void endScreenDraw (SDL_Surface *destination);

#endif
