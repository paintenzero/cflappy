#include "walls.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX(a,b) \
({ __typeof__ (a) _a = a; \
    __typeof__ (b) _b = b; \
    _a>_b?_a:_b; })

#define MIN(a,b) \
({ __typeof__ (a) _a = a; \
    __typeof__ (b) _b = b; \
    _a<_b?_a:_b; })

const int DISTANCE_BETWEEN_WALLS = 200; //
const int WALL_GAP = 100; //
const int STARTING_OFFSET = 460; //will be added to width of the screen
int MIN_WALL_HEIGHT = 0; //will be set in runtime... (wallsReset depending on wallImage height)
int MAX_WALL_HEIGHT = 0; //will be set in runtime... (wallsReset depending on wallImage height)

extern SDL_Rect lightWallClip[2];
extern SDL_Rect darkWallClip[2];
SDL_Rect *upperWallClip;
SDL_Rect *lowerWallClip;

extern float scrollSpeed;
int *walls = NULL;
unsigned int wallsCnt; //max number of walls can be drawn on screen
static float currentOffset; //for side scrolling

SDL_Rect offset;
SDL_Rect clip;
unsigned int scoreGiven; //stores flag if we gave point for current wall
unsigned int halfWallWidth;

/**
 * Generates a new wall with a hole
 */ 
int wallGen ();

void wallsDestroy ()
{
  if (NULL!=walls)
  {
    free (walls);
  }
}

int wallsReset (WallType type, unsigned int maxWidth, unsigned int maxHeight)
{
  unsigned int i;
  wallsDestroy ();
  if (type==lightWall)
  {
    upperWallClip = &(lightWallClip[0]);
    lowerWallClip = &(lightWallClip[1]);
  }
  if (type==darkWall)
  {
    upperWallClip = &(darkWallClip[0]);
    lowerWallClip = &(darkWallClip[1]);
  }

  currentOffset = STARTING_OFFSET;

  MIN_WALL_HEIGHT = MAX(maxHeight-(*upperWallClip).h-WALL_GAP,10);
  MAX_WALL_HEIGHT = MIN((*upperWallClip).h,maxHeight);
  float w = DISTANCE_BETWEEN_WALLS+(*upperWallClip).w;
  wallsCnt = ceil ((float)maxWidth/w);
  walls = malloc (sizeof(int)*wallsCnt);
  
  int *wallIter = walls;
  for (i=0; i<wallsCnt; ++i)
  {
    *wallIter = wallGen ();
    ++wallIter;
  }

  scoreGiven = 0;
  halfWallWidth = (unsigned int)((*upperWallClip).w/2);
  
  return 0;
}

int wallsStep (unsigned int dt, unsigned int birdX)
{
  currentOffset -= scrollSpeed*(float)dt/1000.0f;
  if (currentOffset<=-(*upperWallClip).w)
  {
    currentOffset = DISTANCE_BETWEEN_WALLS;
    unsigned int i;
    for (i=0; i<wallsCnt-1; ++i)
    {
        walls[i] = walls[i+1];
    }
    walls[wallsCnt-1] = wallGen ();
    scoreGiven = 0;
  }
  if ((currentOffset+halfWallWidth)<birdX && scoreGiven==0){ scoreGiven=1; return 1; }
  return 0;
}

void wallsDraw (SDL_Surface *destination)
{
    unsigned int i;
    int offX;
    for (i=0; i<wallsCnt; ++i)
    {
        clip = (*upperWallClip);
        //upper wall
        offX = round(currentOffset) + i * (DISTANCE_BETWEEN_WALLS + clip.w);
        offset.y = walls[i]-clip.h;
        if (offX<=-clip.w) continue;
        if (offX<0)
        {
            clip.x -= offX;
            clip.w += offX;
            offset.x = 0;
        } else offset.x = offX;
        if (offset.y<0)
        {
            clip.y -= offset.y;
            clip.h += offset.y;
            offset.y = 0;
        }
        SDL_BlitSurface (spritesheet, &clip, destination, &offset);
        //lower wall
        offset.y = walls[i]+WALL_GAP;
        clip = (*lowerWallClip);
        if (offX<0)
        {
            clip.x -= offX;
            clip.w += offX;
        }
        clip.h = destination->h-WALL_GAP-walls[i];
        SDL_BlitSurface (spritesheet, &clip, destination, &offset);
    }
}

int wallGen ()
{
  int r = rand()%(MAX_WALL_HEIGHT-MIN_WALL_HEIGHT);
  return r+MIN_WALL_HEIGHT;
}

unsigned int wallsCheckCollisson (int x, int y, int w, int h)
{
    int offX = round (currentOffset);
    if (offX<(x+w) && (offX+(*upperWallClip).w)>(x))
    {
        if (y>walls[0] && (y+h)<walls[0]+WALL_GAP) return 0;
        else return 1;
    }
    return 0;
}
