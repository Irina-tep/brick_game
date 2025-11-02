#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <stdbool.h>
#include <unistd.h>

#include "../../gui/cli/interface.h"

#define ESCAPE 27
#define ENTER_KEY 10
#define ACTION_BUTTON 32
#define PAUSE_BUTTON 112
#define START_BUTTON 115

#define SPEED 500
#define SPEED_STEP 30
#define NEW_LEVEL_THRESHOLD 600
#define MAX_LEVEL 10

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

void updateUserAction();
void userInput(UserAction_t action, bool hold);
void start_game();
int figure_attached();
void move_left();
void move_right();
void move_down();
void rotate_figure();
int rotate_is_possible(int **new_figure);
void pause_game();
void accelerate_move_left();
void accelerate_move_right();
void accelerate_move_down();
void hard_drop();

#endif