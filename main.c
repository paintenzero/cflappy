#include "game.h"
#include "stdio.h"
#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

#define PRINT_ERROR_TERMINATE {\
    printErrorDescription (gameError); \
    return gameError; \
}

const int FRAMES_PER_SECOND = 60; //maximum frames per second

int gameError;

void oneIter ();
void printErrorDescription (int error);

/**
 * Main function
 */
int main (int argc, char *argv[])
{
  if ((gameError=gameCreate ())!=0)
    PRINT_ERROR_TERMINATE


  // Game loop starts here!
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(oneIter, 0, 1);
#else
  while (0==gameShouldQuit())
  {
    oneIter();
    if ((gameError=gameGetError())!=0)
    {
      printErrorDescription (gameError);
      break;
    }
  }
#endif

  gameDestroy ();
  return 0;
}

/**
 * One iteration of the game
 */
void oneIter ()
{
  gamePollEvent ();
  gameLogicStep ();
  gameDraw ();
}

/**
 * Prints text description of error given
 * @param error
 */
void printErrorDescription (int error)
{
  switch (error)
  {
    case -1:
      printf ("Unable to initialize SDL");
      break;
    case -2:
      printf ("Unable to create a window");
      break;
    case -3:
      printf ("Unable to flip the screen");
      break;
    case -4:
      printf ("Unable to load spritesheet");
    case -7:
      printf ("Unable to open background image");
      break;
    case -8:
      printf ("Unable to open bird image");
      break;
    case -9:
      printf ("Unable to create start screen");
      break;
    case -10:
      printf ("Unable to create ready screen");
      break;
    case -11:
      printf ("Unable to create walls");
      break;
    default:
      printf ("Unknown error #%d", error);
      break;
  }
  printf ("\n");
}
