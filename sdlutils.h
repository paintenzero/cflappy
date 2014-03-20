/* 
 * File:   sdlutils.h
 * Author: sergey
 */

#ifndef SDLUTILS_H
#define	SDLUTILS_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

SDL_Surface *screen;
SDL_Surface *spritesheet;

/**
 * Initializes SDL
 */
int sdlInit ();
/**
 * Terminates SQL
 */
void sdlClose ();
/**
 * Loads optimized image
 * @param filename path to file to load
 * @param alpha 0 if image doesn't use transparency 1 otherwise
 * @return SDL_Surface loaded image
 */
SDL_Surface *loadImage (char *filename, int alpha);

/**
 * Writes numbers with medium fonts from right to left
 * @param num number to write
 * @param SDL_Rect lower right point to draw from
 * @param SDL_Surface* surface to draw into
 */
void writeMediumNumRightAligned (int num, SDL_Rect rightPos, SDL_Surface *destination);
/**
 * Writes numbers with large fonts centered to point
 * @param num number to write
 * @param SDL_Rect lower center point to draw from
 * @param SDL_Surface* surface to draw into
 */
void writeLargeNumCentered (int num, SDL_Rect pos, SDL_Surface *destination);

#endif	/* SDLUTILS_H */

