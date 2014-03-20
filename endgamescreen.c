#include "endgamescreen.h"

extern SDL_Rect gameOverClip;
extern SDL_Rect endCardClip;

extern SDL_Rect silverMedalClip;
extern SDL_Rect goldMedalClip;
extern SDL_Rect medalPos;

unsigned int showMedal = 0;
unsigned int showScore = 10;
unsigned int showMostScore = 10;
SDL_Rect scoreRightPos = {204,52,0,0};
SDL_Rect mostRightPos = {204,88,0,0};

int endScreenCreate ()
{
    return 0;
}

void endScreenDestroy ()
{
}

void endScreenShowResult (unsigned int score, unsigned int most, unsigned int medal)
{
    showScore = score;
    showMostScore = most;
    showMedal = medal;
}

void endScreenDraw (SDL_Surface *destination)
{
    SDL_Rect offset;
    offset.x = (destination->w-gameOverClip.w)/2;
    offset.y = 100;
    SDL_BlitSurface (spritesheet, &gameOverClip, destination, &offset);
    
    //game card
    offset.x = (destination->w-endCardClip.w)/2;
    offset.y += gameOverClip.h + 50;
    SDL_BlitSurface (spritesheet, &endCardClip, destination, &offset);

    //show medal
    if (showMedal!=0)
    {
        offset.x += medalPos.x;
        offset.y += medalPos.y;
        if (showMedal==1) //gold
            SDL_BlitSurface (spritesheet, &goldMedalClip, destination, &offset);
        if (showMedal==2) //silver
            SDL_BlitSurface (spritesheet, &silverMedalClip, destination, &offset);
        offset.x -= medalPos.x;
        offset.y -= medalPos.y;
    }
    //show score
    offset.x += scoreRightPos.x;
    offset.y += scoreRightPos.y;
    writeMediumNumRightAligned (showScore, offset, destination);
    offset.x -= scoreRightPos.x;
    offset.y -= scoreRightPos.y;

    //"most" score
    offset.x += mostRightPos.x;
    offset.y += mostRightPos.y;
    writeMediumNumRightAligned (showMostScore, offset, destination);
}


