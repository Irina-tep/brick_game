#include "game_info.h"

GameInfo_t updateCurrentState() {
  State_t *state = getCurrentState();
  GameInfo_t info;
  int **field = create_matrix(FIELD_H, FIELD_W);
  copy_matrix(state->field, field, FIELD_H, FIELD_W);
  if (state->figure != NULL) {
    for (int i = 0; i < state->size_figure; i++) {
      for (int j = 0; j < state->size_figure; j++) {
        int new_coord_x = state->coord_x + i;
        int new_coord_y = state->coord_y + j;
        if (state->figure[i][j] == 1 && new_coord_x >= 0 &&
            new_coord_x < FIELD_H && new_coord_y < FIELD_W) {
          field[new_coord_x][new_coord_y] = 1;
        }
      }
    }
  }

  info.field = field;
  info.score = state->score;
  info.level = state->level;
  info.speed = state->speed;
  int **next = create_matrix(4, 4);
  if (state->next != NULL && state->size_nextfigure > 0) {
    int copy_size = (state->size_nextfigure < 4) ? state->size_nextfigure : 4;
    for (int i = 0; i < copy_size; i++) {
      for (int j = 0; j < copy_size; j++) {
        if (i < state->size_nextfigure && j < state->size_nextfigure) {
          next[i][j] = state->next[i][j];
        }
      }
    }
  }
  info.next = next;
  int hight_score;
  FILE *file = fopen("max_score.txt", "r");
  fscanf(file, "%d", &hight_score);
  fclose(file);
  info.high_score = hight_score;
  info.pause = None;
  if (state->status == Initial) {
    info.pause = GameStart;
  }
  if (state->pause == 1) {
    info.pause = GamePause;
  }
  if (state->status == GameOver) {
    info.pause = YouLost;
    init_state();
  }
  return info;
}
