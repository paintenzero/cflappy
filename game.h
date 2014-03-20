#ifndef _GAME_H_
#define _GAME_H_

#include "sdlutils.h"

typedef enum GameState
{
  start,
  getReady,
  game,
  gameover
} GameState;

/**
 * Creates a game
 * @return int -1 if SDL not initialized
 *             -2 if window is not created
 */
int gameCreate ();

/**
 * Destroys a game
 */
void gameDestroy ();

/**
 * Returns 1 if game should terminate
 */
int gameShouldQuit ();

/**
 * Returns current game error
 */
int gameGetError ();

/**
 * Start a round
 */
void roundStart ();

/**
 * Polls SDL events
 */
void gamePollEvent ();

/**
 * Game logic step
 */
void gameLogicStep ();

/**
 * Draw one frame of the game
 */
void gameDraw ();
#endif
