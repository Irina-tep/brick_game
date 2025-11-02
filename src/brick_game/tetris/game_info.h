#ifndef GAME_INFO_H
#define GAME_INFO_H

#include "tetris_fsm.h"

#define FIELD_H 20
#define FIELD_W 10

typedef enum {
  None,
  GameStart,
  GamePause,
  YouLost,
} Banner;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

GameInfo_t updateCurrentState();

#endif