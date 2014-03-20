#include "bird.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const unsigned int ANIMATION_SPEED = 100; //speed for frame change
const unsigned int FRAMES_COUNT = 3; //number of animation frames

static SDL_Surface *birdImage[3];
float posY; //current y position of the bird
float speedY; //speed of the bird going down
const float gravityForce = 800.0f; //gravity
const float upForce = 500.0f;
unsigned int curImageIndex;
unsigned int curImageIndexTicks; //for storing how long we shown this frame

char *images[] = {
    "images/bluebird1.png", "images/bluebird2.png", "images/bluebird3.png",
    "images/greenbird1.png", "images/greenbird2.png", "images/greenbird3.png",
    "images/pinkbird1.png", "images/pinkbird2.png", "images/pinkbird3.png",
};

int birdCreate (BirdType type)
{
  unsigned int i, fnoffset;
  if (type==blue) fnoffset = 0;
  else if (type==green) fnoffset = 3;
  else if (type==pink) fnoffset = 6;
  else return -8;


  //load image selected
  for (i=0; i<FRAMES_COUNT; ++i){
    birdImage[i] = loadImage (images[fnoffset+i], 1);
    if (NULL==birdImage[i])
    {
      return -8;
    }
  }

  posY = 100;
  speedY = 0;
  curImageIndex = 0;
  return 0;
}

void birdDestroy ()
{
  if (NULL!=birdImage)
  {
    unsigned int i;
    for (i=0; i<FRAMES_COUNT; ++i)
    {
        SDL_FreeSurface (birdImage[i]);
    }
    //free (birdImage);
  }
}

int birdX (){ return 100; }
int birdY (){ return (int)posY; }
int birdW (){ return birdImage[0]->w; }
int birdH (){ return birdImage[0]->h; }

void birdLogicStep (unsigned int dt)
{
  float dt_s = (float)dt/1000.0f; //time diff in seconds
  speedY += gravityForce*dt_s;
  posY += speedY*dt_s;
  //animation
  if (curImageIndex!=0)
  {
    if (curImageIndexTicks>ANIMATION_SPEED)
    {
        ++curImageIndex;
        if (curImageIndex==FRAMES_COUNT) curImageIndex = 0;
        curImageIndexTicks = 0;
    }
    else
    {
        curImageIndexTicks += dt;
    }
  }
}

void birdFlyUp ()
{
  speedY -= upForce;
  curImageIndex = 1;
  curImageIndexTicks = 0;
}

void birdDraw (SDL_Surface *destination)
{
  SDL_Rect offset;
  offset.x = 100;
  offset.y = posY;
  int angle = -speedY/200.0f*5;

  if (angle!=0)
  {
    SDL_Surface *rotated = rotozoomSurface (birdImage[curImageIndex], angle, 1.0, 0);
    offset.x += birdImage[curImageIndex]->w/2 - rotated->w/2;
    offset.y += birdImage[curImageIndex]->h/2 - rotated->h/2;
    SDL_BlitSurface (rotated, NULL, destination, &offset);
    SDL_FreeSurface (rotated);
  }
  else
  {
    SDL_BlitSurface (birdImage[curImageIndex], NULL, destination, &offset);
  }
}
