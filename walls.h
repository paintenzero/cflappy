#include "sdlutils.h"

typedef enum WallType 
{
  darkWall,
  lightWall
} WallType;

/**
 * Destroys walls
 */
void wallsDestroy ();

/**
 * Reset walls to given type
 * @param type darkWall or lightWall
 */
int wallsReset (WallType type, unsigned int maxWidth, unsigned int maxHeight);

/**
 * Logic step for walls
 * @param dt time difference since previous step
 * @return how many score to give to player
 */
int wallsStep (unsigned int dt, unsigned int birdX);

/**
 * Draws walls on a screen
 * @param destination surface to draw to
 */
void wallsDraw (SDL_Surface *destination);

/**
 * Checks collision of the box with first wall on a way
 * Also checks collision with floor and ceil
 * Actually checks if the box is in a gap
 * @param x
 * @param y
 * @param w
 * @param h
 * @return 1 if collided 0 otherwise
 */
unsigned int wallsCheckCollisson (int x, int y, int w, int h);
