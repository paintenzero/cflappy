#ifndef __BIRD_H__
#define __BIRD_H__

#include "sdlutils.h"

typedef enum BirdType 
{
  blue,
  green,
  pink
} BirdType;

/**
 * Creates a bird
 * @return 0 on success -8 on bird create failed
 */
int birdCreate (BirdType type);

/**
 * Deletes a bird
 */
void birdDestroy ();

/**
 * Returns current bird x
 * @return int
 */
inline int birdX ();
/**
 * Returns current bird y
 * @return int
 */
inline int birdY ();
/**
 * Returns current bird width 
 * @return int
 */
inline int birdW ();
/**
 * Returns current bird height
 * @return int
 */
inline int birdH ();

/**
 * Performs bird's logic step
 * @param dt time in ms from last step
 */
void birdLogicStep (unsigned int dt);

/**
 * Makes bird to fly up
 */
void birdFlyUp ();

/**
 * Draws a bird on the screen
 * @param destination surface to blit into
 */
void birdDraw (SDL_Surface *destination);

#endif //__BIRD_H__
