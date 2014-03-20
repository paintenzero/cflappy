#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "sdlutils.h"

typedef enum BackgroundType
{
  light,
  dark
} BackgroundType;

/**
 * Creates a background
 */
int backgroundCreate (BackgroundType type);

/**
 * Destroys background
 */
void backgroundDestroy ();

/**
 * Logic step for background
 */
void backgroundLogicStep (unsigned int dt);
/**
 * Draws current background to the screen
 */
void backgroundDraw (SDL_Surface *destination);

#endif
