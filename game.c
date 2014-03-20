#include "game.h"
#include "background.h"
#include "bird.h"
#include "walls.h"
#include "startscreen.h"
#include "readyscreen.h"
#include "endgamescreen.h"
#include <time.h>
#include <stdlib.h>

extern const int FRAMES_PER_SECOND; //maximum frames per second

SDL_Event event;
int b_ShouldQuit; //flag if the game should quit
int gameError; //holds game error
unsigned int lastFrameTicks; //tick of last frame draw
unsigned int lastStepTicks; //ticks of last logic step
int b_SpaceKeyReleased; //space was released
int b_SpaceKeyPressed; //space was released

unsigned int b_Collided; 
unsigned int score;
unsigned int most;
unsigned int t_gameOver; //holds ticks when game was over (for preventing reacting on immediate spacebar key)

GameState aState;
SDL_Surface *spritesheet;
extern SDL_Rect largeFontClip[10];

/**
 * Draw ingame score on screen
 */
void scoreDraw (SDL_Surface *destination);

int gameCreate ()
{
  b_ShouldQuit = 0;
  lastFrameTicks = 0;
  //initialize sdl
  if ((gameError=sdlInit ())!=0)
    return gameError;
  //load spritesheet file
  spritesheet = loadImage ("images/spritesheet.png",1);
  if (NULL==spritesheet)
    return gameError=-4;
   
  //create background
  if ((gameError=backgroundCreate (light))!=0)
    return gameError;
  if ((gameError=startScreenCreate ())!=0)
    return gameError;
  if ((gameError=readyScreenCreate ())!=0)
    return gameError;
  if ((gameError=endScreenCreate ())!=0)
    return gameError;
  srand (time(NULL));

  b_SpaceKeyReleased = 1;
  b_SpaceKeyPressed = 0;
  aState = start;
  most = 0;
  return 0;
}

void gameDestroy ()
{
  backgroundDestroy ();
  startScreenDestroy ();
  readyScreenDestroy ();
  endScreenDestroy ();
  birdDestroy ();
  wallsDestroy ();
  if (NULL!=spritesheet) SDL_FreeSurface (spritesheet);
  sdlClose ();
}

int gameShouldQuit ()
{
  return b_ShouldQuit;
}

int gameGetError ()
{
  return gameError;
}


void roundStart ()
{
  //create random background
  backgroundDestroy ();
  int r = rand()%2;
  if (r==0)
  {
    if ((gameError=backgroundCreate (light))!=0)
      return;
    if ((gameError=wallsReset (lightWall,screen->w,screen->h))!=0)
      return;
  }
  else
  {
    if ((gameError=backgroundCreate (dark))!=0)
      return;
    if ((gameError=wallsReset (darkWall,screen->w,screen->h))!=0)
      return;
  }

  //create random bird
  birdDestroy ();
  r = rand()%3;
  BirdType bt;
  switch (r)
  {
      case 0: r=blue; break;
      case 1: r=green; break;
      case 2: r=pink; break;
  }
  if ((gameError=birdCreate (r))!=0)
  {
    return;
  }
  b_Collided = 0;
  score = 0;

  readyScreenReset ();
  aState = getReady;
}
/**
 * Ends the game
 */
void gameOver ()
{
  t_gameOver = SDL_GetTicks ();
  unsigned int medal = 0;
  if (most<score){
    most = score;
    medal = 1;
  }
  else if (most==score){
    medal=2;
  }

  endScreenShowResult (score, most, medal);
  aState = gameover;
}

/* ------------ Iteration logic ---------- */
void gamePollEvent ()
{
  b_SpaceKeyPressed = 0;
  while (SDL_PollEvent (&event))
  {
    if (event.type==SDL_QUIT) b_ShouldQuit = 1; 
    else if (event.type==SDL_KEYDOWN)
    {
      switch (event.key.keysym.sym)
      {
        case SDLK_SPACE:
          if (b_SpaceKeyReleased)
          {
            b_SpaceKeyPressed = 1;
            b_SpaceKeyReleased = 0;
          }
          break;
      }
    }
    else if (event.type==SDL_KEYUP)
    {
      switch (event.key.keysym.sym)
      {
        case SDLK_SPACE:
          b_SpaceKeyPressed = 0;
          b_SpaceKeyReleased = 1;
          break;
        case SDLK_ESCAPE:
          b_ShouldQuit = 1;
          break;
      }
    }
  }
}

void gameLogicStep ()
{
  unsigned int curTicks = SDL_GetTicks ();
  unsigned int dt = curTicks - lastStepTicks;
  backgroundLogicStep (dt);

  switch (aState)
  {
    case start:
      if (b_SpaceKeyPressed) roundStart ();
      break;
    case getReady:
      if (readyScreenStep (dt)<=0)
        aState = game;
      break;
    case game:
      //check collision
      b_Collided = 0;
      if (birdY()<0 || (birdY()+birdH())>screen->h) b_Collided = 1;
      b_Collided += wallsCheckCollisson (birdX(), birdY(),birdW(),birdH());
      if (b_Collided!=0){
        gameOver();
        return;
      }
      if (b_SpaceKeyPressed) birdFlyUp ();
      birdLogicStep (dt);
      score += wallsStep (dt, birdX());
      break;
    case gameover:
      if (b_SpaceKeyPressed && curTicks-t_gameOver>500) aState = start;
  }
  lastStepTicks = curTicks;
}

void gameDraw ()
{
  unsigned int curTicks = SDL_GetTicks ();
  if ((curTicks-lastFrameTicks)<1000/FRAMES_PER_SECOND){
    //pause for next frame
#ifndef EMSCRIPTEN
    SDL_Delay ( (1000/FRAMES_PER_SECOND)-(curTicks-lastFrameTicks) );
#endif
    return;
  }    

  SDL_FillRect(screen, NULL, 0x000000); //fill screen with black color
  backgroundDraw (screen);
  
  switch (aState)
  {
    case start:
      startScreenDraw (screen);
      break;
    case getReady:
      readyScreenDraw (screen);
      break;
    case game:
      birdDraw (screen);  
      wallsDraw (screen);
      scoreDraw (screen);
      break;
    case gameover:
      endScreenDraw (screen);
      break;
  }

  //show screen
  if (SDL_Flip (screen)==-1) 
  {
    gameError = -3;
  }
  lastFrameTicks = curTicks; //save current ticks
}

void scoreDraw (SDL_Surface *destination)
{
    SDL_Rect scorePoint = {destination->w/2,100,0,0};
    writeLargeNumCentered (score, scorePoint, destination);
}
