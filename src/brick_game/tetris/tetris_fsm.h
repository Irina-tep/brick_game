
#ifndef TETRIS_FSM_H
#define TETRIS_FSM_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

typedef enum { Initial, Spawn, Moving, Shifting, Attaching, GameOver } Status_t;

typedef struct {
  int status;
  int **field;
  int **figure;
  int size_figure;
  int **next;
  int size_nextfigure;
  int coord_x;
  int coord_y;

  int score;
  int level;
  int speed;
  int pause;

  unsigned long long start_time;
  unsigned long long left_time;

} State_t;

typedef enum { O_fig, I_fig, S_fig, Z_fig, L_fig, J_fig, T_fig } figure;

State_t *getCurrentState();
int **create_matrix(int row, int col);
int **create_figure(int *size_figure);

void remove_matrix(int **matrix, int size);
void copy_matrix(int **matr1, int **matr2, int row, int col);
void rotate(int **new_figure, int **old_figure, int size);

void init_state();
unsigned long long current_timeMs();
unsigned long long procces_timer();
void spawn_new_figure();
void shift_figure();
void max_score();
void update_level();
void delete_row();
void attach_figure();
void game_over();
#endif