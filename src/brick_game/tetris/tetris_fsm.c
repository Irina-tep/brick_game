#include "tetris_fsm.h"

#include "user_input.h"

State_t *getCurrentState() {
  static State_t state;
  return &state;
}

int **create_matrix(int row, int col) {
  int **matrix = (int **)malloc(row * sizeof(int *));
  for (int i = 0; i < row; i++) {
    matrix[i] = (int *)calloc(col, sizeof(int));
  }

  return matrix;
}

int **create_figure(int *size_figure) {
  int type_figure = rand() % 7;
  if (type_figure == I_fig)
    *size_figure = 4;
  else if (type_figure == O_fig)
    *size_figure = 2;
  else
    *size_figure = 3;
  int **figure = create_matrix(*size_figure, *size_figure);
  int **temp = create_matrix(*size_figure, *size_figure);
  if (type_figure == I_fig) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[0][3] = 1;
  } else if (type_figure == O_fig) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
  } else if (type_figure == S_fig) {
    figure[0][1] = 1;
    figure[0][2] = 1;
    figure[1][0] = 1;
    figure[1][1] = 1;
  } else if (type_figure == Z_fig) {
    figure[0][0] = 1;
    figure[0][1] = 1;
    figure[1][1] = 1;
    figure[1][2] = 1;
  } else if (type_figure == L_fig) {
    figure[0][0] = 1;
    figure[1][0] = 1;
    figure[2][0] = 1;
    figure[2][1] = 1;
  } else if (type_figure == J_fig) {
    figure[0][2] = 1;
    figure[1][2] = 1;
    figure[2][2] = 1;
    figure[2][1] = 1;
  } else {
    figure[1][1] = 1;
    figure[2][0] = 1;
    figure[2][1] = 1;
    figure[2][2] = 1;
  }
  int rotatoins = rand() % 4;
  for (int i = 0; i < rotatoins; i++) {
    rotate(temp, figure, *size_figure);
    copy_matrix(temp, figure, *size_figure, *size_figure);
  }
  remove_matrix(temp, *size_figure);
  return figure;
}

void remove_matrix(int **matrix, int size) {
  if (matrix != NULL) {
    for (int i = 0; i < size; i++) {
      if (matrix[i] != NULL) {
        free(matrix[i]);
      }
    }
    free(matrix);
  }
}

void copy_matrix(int **matr1, int **matr2, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      matr2[i][j] = matr1[i][j];
    }
  }
}

void rotate(int **new_figure, int **old_figure, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      new_figure[i][j] = 0;
    }
  }
  if (size == 4) {
    if (old_figure[0][0] == 1) {
      new_figure[0][1] = 1;
      new_figure[1][1] = 1;
      new_figure[2][1] = 1;
      new_figure[3][1] = 1;
    } else {
      new_figure[0][0] = 1;
      new_figure[0][1] = 1;
      new_figure[0][2] = 1;
      new_figure[0][3] = 1;
    }
  } else {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        new_figure[j][size - i - 1] = old_figure[i][j];
      }
    }
  }
}

void init_state() {
  State_t *state = getCurrentState();
  if (state->field != NULL) {
    remove_matrix(state->field, FIELD_H);
  }
  if (state->figure != NULL) {
    remove_matrix(state->figure, state->size_figure);
  }
  if (state->next != NULL) {
    remove_matrix(state->next, state->size_nextfigure);
  }
  state->status = Initial;
  int **field = create_matrix(FIELD_H, FIELD_W);
  state->field = field;
  state->score = 0;
  state->level = 1;
  state->speed = SPEED;
  state->left_time = state->speed;
  state->start_time = current_timeMs();
  state->pause = 0;
  state->coord_x = 0;
  state->coord_y = 4;

  state->figure = NULL;
  state->size_figure = 0;

  int size_nextfigure = 0;
  state->next = create_figure(&size_nextfigure);
  state->size_nextfigure = size_nextfigure;

  srand(current_timeMs());
}

unsigned long long current_timeMs() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (unsigned long long)(tv.tv_sec) * 1000 +
         (unsigned long long)(tv.tv_usec) / 1000;
}

unsigned long long procces_timer() {
  State_t *state = getCurrentState();
  unsigned long long left_time;
  if (state->status == Initial) {
    left_time = -1;
  } else {
    unsigned long long current_time = current_timeMs();
    unsigned long long elapsed_time = current_time - state->start_time;
    if (elapsed_time >= state->left_time) {
      left_time = 0;
    } else {
      state->left_time -= elapsed_time;
      state->start_time = current_time;
      left_time = state->left_time;
    }
  }
  return left_time;
}

void spawn_new_figure() {
  State_t *state = getCurrentState();
  if (state->figure != NULL) {
    remove_matrix(state->figure, state->size_figure);
  }
  state->figure = state->next;
  state->size_figure = state->size_nextfigure;
  state->coord_x = -1;
  if (state->size_figure == 2) {
    state->coord_y = 4;
  } else {
    state->coord_y = 3;
  }
  int size_nextfigure;
  int **next = create_figure(&size_nextfigure);
  state->next = next;
  state->size_nextfigure = size_nextfigure;
  state->status = Moving;
  state->start_time = current_timeMs();
  state->left_time = state->speed;
}

void shift_figure() {
  State_t *state = getCurrentState();
  int attached = figure_attached();
  if (attached == 0) {
    (state->coord_x)++;
    state->start_time = current_timeMs();
    state->left_time = state->speed;
    state->status = Moving;
  } else {
    state->status = Attaching;
  }
}

void max_score() {
  State_t *state = getCurrentState();
  FILE *file;
  file = fopen("max_score.txt", "r");
  int hight_score;
  fscanf(file, "%d", &hight_score);
  fclose(file);

  if (state->score > hight_score) {
    file = fopen("max_score.txt", "w");
    fprintf(file, "%d", state->score);
    fclose(file);
  }
}

void update_level() {
  State_t *state = getCurrentState();
  int new_level = state->score / NEW_LEVEL_THRESHOLD + 1;
  if (new_level > MAX_LEVEL) {
    new_level = MAX_LEVEL;
  }
  state->speed -= (new_level - state->level) * SPEED_STEP;
  state->level = new_level;
}

void delete_row() {
  State_t *state = getCurrentState();
  int total_del_row = 0;
  for (int i = 0; i < FIELD_H; i++) {
    int count_del_row = 0;
    for (int j = 0; j < FIELD_W; j++) {
      count_del_row += state->field[i][j];
    }
    if (count_del_row == FIELD_W) {
      for (int m = i; m > 0; m--) {
        for (int k = 0; k < FIELD_W; k++) {
          state->field[m][k] = state->field[m - 1][k];
        }
      }
      for (int n = 0; n < FIELD_W; n++) {
        state->field[0][n] = 0;
      }
      i--;
      total_del_row++;
    }
  }
  if (total_del_row == 1) {
    state->score += 100;
  } else if (total_del_row == 2) {
    state->score += 300;
  } else if (total_del_row == 3) {
    state->score += 700;
  } else if (total_del_row == 4) {
    state->score += 1500;
  }
  max_score();
  update_level();
}

void attach_figure() {
  State_t *state = getCurrentState();
  int game_over = 0;

  for (int i = 0; i < state->size_figure; i++) {
    for (int j = 0; j < state->size_figure; j++) {
      if (state->figure[i][j] == 1) {
        int new_coord_x = state->coord_x + i;
        int new_coord_y = state->coord_y + j;

        if (new_coord_x >= 0 && new_coord_x < FIELD_H && new_coord_y >= 0 &&
            new_coord_y < FIELD_W) {
          state->field[new_coord_x][new_coord_y] = 1;
        } else if (new_coord_x < 0) {
          game_over = 1;
        }
      }
    }
  }
  if (game_over == 1) {
    state->status = GameOver;
  } else {
    delete_row();
    state->status = Spawn;
  }
}

void game_over() {
  State_t *state = getCurrentState();
  if (state->figure != NULL && state->size_figure > 0) {
    remove_matrix(state->figure, state->size_figure);
    state->figure = NULL;
  }
  if (state->next != NULL && state->size_nextfigure > 0) {
    remove_matrix(state->next, state->size_nextfigure);
    state->next = NULL;
  }
  if (state->field != NULL) {
    remove_matrix(state->field, FIELD_H);
    state->field = NULL;
  }
}
