#include "sdlutils.h"

const int SCREEN_WIDTH = 700;  //screen width
const int SCREEN_HEIGHT = 510;  //screen height
const int SCREEN_BPP = 32; //screen color depth

///////////////////// Spritesheets /////////////////
SDL_Rect logoClip = {701,182,179,48};
SDL_Rect tapClip = {584,182,114,98};
SDL_Rect readyClip = {590,116,184,52};

SDL_Rect gameOverClip = {790,116,192,44};
SDL_Rect endCardClip = {6,518,226,114};
SDL_Rect silverMedalClip = {242,516,44,44};
SDL_Rect goldMedalClip = {242,564,44,44};
SDL_Rect medalPos = {26,42,0,0};

SDL_Rect lightBackgroundClip = {0,0,287,510};
SDL_Rect darkBackgroundClip = {292,0,287,510};

SDL_Rect lightWallClip[] = {
{56,646,52,320},
{0,646,52,320}}; //0-upper, 1-lower
SDL_Rect darkWallClip[] = {
{112,646,52,320},
{168,646,52,320}}; //0-upper, 1-lower

//Fonts
SDL_Rect mediumFontClip[] = {
{274,612,14,20}, 
{274,954,14,20},
{274,979,14,20},
{262,1002,14,20},
{1004,0,14,20},
{1004,24,14,20},
{1010,52,14,20},
{1010,84,14,20},
{586,484,14,20},
{622,412,14,20}};

SDL_Rect largeFontClip[] = {
{992,120,24,36}, 
{268,910,24,36},
{584,320,24,36},
{612,320,24,36},
{640,320,24,36},
{668,320,24,36},
{584,368,24,36},
{612,368,24,36},
{640,368,24,36},
{668,368,24,36}};



int sdlInit ()
{
  //Initialize SDL
  if (SDL_Init (SDL_INIT_EVERYTHING)==-1)
  {
    return -1;
  }
  //Create a window
  screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
  if (NULL==screen)
  {
    return -2;
  }
  SDL_WM_SetCaption ("Flappy Arcade", NULL);
  //Enable key repeat
  if (SDL_EnableKeyRepeat (0, SDL_DEFAULT_REPEAT_INTERVAL)!=0)
  {
    return -5;
  }
  return 0;
}

void sdlClose ()
{
  SDL_Quit ();
}
 
SDL_Surface *loadImage (char *filename, int alpha)
{
  SDL_Surface *loadedImage = NULL;
  SDL_Surface *optimizedImage = NULL;
  loadedImage = IMG_Load (filename);
#ifdef EMSCRIPTEN
  return loadedImage;
#else
  if (loadedImage!=NULL)
  {
    if (1==alpha)
      optimizedImage = SDL_DisplayFormatAlpha (loadedImage);
    else
      optimizedImage = SDL_DisplayFormat (loadedImage);
    SDL_FreeSurface (loadedImage); 
  }
  return optimizedImage;
#endif
}

void writeMediumNumRightAligned (int num, SDL_Rect rightPos, SDL_Surface *destination)
{
    SDL_Rect offset = rightPos;
    offset.x -= mediumFontClip[0].w;
    offset.y -= mediumFontClip[0].h;
    if (num==0)
    {
        SDL_BlitSurface (spritesheet, &mediumFontClip[0], destination, &offset);
        return;
    }
    else
    {
        unsigned int n;
        while (num!=0)
        {
            n = num % 10;
            SDL_BlitSurface (spritesheet, &mediumFontClip[n], destination, &offset);
            offset.x -= mediumFontClip[0].w + 1;
            num /= 10;
        }
    }
}

void writeLargeNumCentered (int num, SDL_Rect pos, SDL_Surface *destination)
{
    pos.y -= largeFontClip[0].h;
    if (num==0)
    {
       pos.x -= (int)largeFontClip[0].w/2;
       SDL_BlitSurface (spritesheet, &largeFontClip[0], destination, &pos);
       return;
    }
    else
    {
        unsigned int n=num, cnt, totalWidth;
        for (cnt=0; n!=0; n/=10);
        totalWidth = cnt*(largeFontClip[0].w+1)-1;
        pos.x += (int)totalWidth/2;
        while (num!=0)
        {
            n = num % 10;
            pos.x -= largeFontClip[0].w;
            SDL_BlitSurface (spritesheet, &largeFontClip[n], destination, &pos);
            --pos.x;
            num /= 10;
        }
    }
}
