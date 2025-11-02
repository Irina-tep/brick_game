#include <check.h>
#include <stdlib.h>

#include "../brick_game/tetris/game_info.h"
#include "../brick_game/tetris/user_input.h"
#include "../gui/cli/interface.h"

START_TEST(test_HighScore) {
  State_t *state = getCurrentState();
  init_state();
  FILE *file = fopen("max_score.txt", "w");
  fprintf(file, "1234");
  fclose(file);

  max_score();
  GameInfo_t game = updateCurrentState();
  ck_assert_int_eq(game.high_score, 1234);

  state->score = 5678;
  max_score();
  file = fopen("max_score.txt", "r");
  int high_score;
  fscanf(file, "%d", &high_score);
  fclose(file);

  ck_assert_int_eq(high_score, 5678);
}
END_TEST

START_TEST(test_init1) {
  State_t *state = getCurrentState();
  init_state();
  ck_assert_int_eq(state->score, 0);
  ck_assert_int_eq(state->level, 1);
  ck_assert_int_eq(state->speed, 500);
  ck_assert_int_eq(state->pause, 0);

  game_over();
}
END_TEST

START_TEST(test_init2) {
  State_t *state = getCurrentState();
  init_state();
  ck_assert_ptr_nonnull(state->field);
  spawn_new_figure();
  ck_assert_int_eq(state->coord_x, -1);
  shift_figure();
  ck_assert_int_eq(state->coord_x, 0);
  game_over();
}
END_TEST

START_TEST(test_init3) {
  State_t *state = getCurrentState();
  init_state();
  ck_assert_ptr_nonnull(state->field);
  spawn_new_figure();
  shift_figure();
  move_left();
  ck_assert_int_eq(state->coord_y, 2);
  game_over();
}
END_TEST

START_TEST(test_UserInputLeft) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  userInput(Left, false);
  ck_assert_int_eq(state->coord_y, 2);
  game_over();
}
END_TEST

START_TEST(test_noleft) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  while (state->coord_y != 0) {
    move_left();
  }
  move_left();
  ck_assert_int_eq(state->coord_y, 0);
  game_over();
}
END_TEST

START_TEST(test_init4) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  move_down();
  ck_assert_int_eq(state->coord_x, 1);
  game_over();
}
END_TEST

START_TEST(test_UserInputDown) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  userInput(Down, false);
  ck_assert_int_eq(state->coord_x, 1);
  game_over();
}
END_TEST

START_TEST(test_init5) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  ck_assert_ptr_nonnull(state->figure);
  shift_figure();
  move_right();
  ck_assert_int_eq(state->coord_y, 4);
  game_over();
}
END_TEST

START_TEST(test_noright) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  while (state->coord_y + state->size_figure != FIELD_W) {
    move_right();
  }
  move_right();
  ck_assert_int_eq(state->coord_y, 10 - state->size_figure);
  game_over();
}
END_TEST

START_TEST(test_UserInputRight) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  userInput(Right, false);
  ck_assert_int_eq(state->coord_y, 4);
  game_over();
}
END_TEST

START_TEST(test_init6) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  hard_drop();
  ck_assert_int_eq(state->coord_x, 19);
  game_over();
}
END_TEST

START_TEST(test_UserInputhard) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  userInput(Up, false);
  ck_assert_int_eq(state->coord_x, 19);
  game_over();
}
END_TEST

START_TEST(test_init7) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  int **temp = create_matrix(state->size_figure, state->size_figure);
  copy_matrix(state->figure, temp, state->size_figure, state->size_figure);
  rotate_figure();
  rotate_figure();
  rotate_figure();
  rotate_figure();
  for (int i = 0; i < state->size_figure; i++) {
    for (int j = 0; j < state->size_figure; j++) {
      ck_assert_int_eq(state->figure[i][j], temp[i][j]);
    }
  }
  remove_matrix(temp, state->size_figure);
  game_over();
}
END_TEST

START_TEST(test_UserInputAction) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  int **temp = create_matrix(state->size_figure, state->size_figure);
  copy_matrix(state->figure, temp, state->size_figure, state->size_figure);
  userInput(Action, false);
  userInput(Action, false);
  userInput(Action, false);
  userInput(Action, false);
  for (int i = 0; i < state->size_figure; i++) {
    for (int j = 0; j < state->size_figure; j++) {
      ck_assert_int_eq(state->figure[i][j], temp[i][j]);
    }
  }
  remove_matrix(temp, state->size_figure);
  game_over();
}
END_TEST

START_TEST(test_pause) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  pause_game();
  ck_assert_int_eq(state->pause, 1);
  game_over();
}
END_TEST

START_TEST(test_UserInputpause) {
  State_t *state = getCurrentState();
  init_state();
  userInput(Pause, false);
  ck_assert_int_eq(state->pause, 1);
  game_over();
}
END_TEST

START_TEST(test_updatelevel) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  shift_figure();
  update_level();
  ck_assert_int_eq(state->level, 1);
  state->score = 10000;
  update_level();
  ck_assert_int_eq(state->level, 10);
  game_over();
}
END_TEST

START_TEST(test_deleterow) {
  State_t *state = getCurrentState();
  init_state();
  for (int j = 0; j < FIELD_W; j++) {
    state->field[19][j] = 1;
  }
  delete_row();
  for (int k = 0; k < FIELD_W; k++) {
    ck_assert_int_eq(state->field[19][k], 0);
  }
  game_over();
}
END_TEST

START_TEST(test_attachfig) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  while (state->coord_x != 19) {
    shift_figure();
  }
  attach_figure();
  int one = 0;
  for (int k = 0; k < FIELD_W; k++) {
    if (state->field[19][k] == 1) {
      one++;
    }
  }
  ck_assert_int_ne(one, 0);
  game_over();
}
END_TEST

START_TEST(test_userInput_terminate) {
  State_t *state = getCurrentState();
  init_state();
  userInput(Terminate, false);
  ck_assert_ptr_eq(state->field, NULL);
}
END_TEST

START_TEST(test_userInput_start) {
  State_t *state = getCurrentState();
  init_state();
  userInput(Start, false);
  ck_assert_int_eq(state->status, 1);
  game_over();
}
END_TEST

START_TEST(test_overflow) {
  State_t *state = getCurrentState();
  init_state();
  for (int j = 0; j < FIELD_W; j++) {
    state->field[j][3] = 1;
    state->field[j][4] = 1;
    state->field[j][5] = 1;
    state->field[j][6] = 1;
  }
  spawn_new_figure();
  shift_figure();
  attach_figure();
  ck_assert_int_eq(state->status, 5);
  game_over();
}
END_TEST

START_TEST(test_pausepause) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  pause_game();
  pause_game();
  ck_assert_int_eq(state->pause, 0);
  game_over();
}
END_TEST

START_TEST(test_terminate) { terminate_game(); }
END_TEST

START_TEST(test_newgame) {
  State_t *state = getCurrentState();
  init_state();
  for (int j = 0; j < FIELD_W; j++) {
    state->field[j][3] = 1;
    state->field[j][4] = 1;
    state->field[j][5] = 1;
    state->field[j][6] = 1;
  }
  spawn_new_figure();
  shift_figure();
  attach_figure();
  ck_assert_int_eq(state->status, 5);
  init_state();
  game_over();
}
END_TEST

START_TEST(test_procces_timer) {
  State_t *state = getCurrentState();
  init_state();
  procces_timer();
  ck_assert_int_eq(state->left_time, 500);
  state->status = Moving;
  procces_timer();
  ck_assert_int_eq(state->left_time, 500);
  game_over();
}
END_TEST

START_TEST(test_spawn) {
  State_t *state = getCurrentState();
  init_state();
  spawn_new_figure();
  while (state->coord_x != 19) {
    shift_figure();
  }
  attach_figure();
  spawn_new_figure();
  ck_assert_int_eq(state->status, 2);
  game_over();
}
END_TEST

Suite *tetris_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Tetris");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_HighScore);
  tcase_add_test(tc_core, test_init1);
  tcase_add_test(tc_core, test_init2);
  tcase_add_test(tc_core, test_init3);
  tcase_add_test(tc_core, test_UserInputLeft);
  tcase_add_test(tc_core, test_noleft);
  tcase_add_test(tc_core, test_init4);
  tcase_add_test(tc_core, test_UserInputDown);
  tcase_add_test(tc_core, test_init5);
  tcase_add_test(tc_core, test_UserInputRight);
  tcase_add_test(tc_core, test_noright);
  tcase_add_test(tc_core, test_init6);
  tcase_add_test(tc_core, test_UserInputhard);
  tcase_add_test(tc_core, test_init7);
  tcase_add_test(tc_core, test_UserInputAction);
  tcase_add_test(tc_core, test_pause);
  tcase_add_test(tc_core, test_UserInputpause);
  tcase_add_test(tc_core, test_updatelevel);
  tcase_add_test(tc_core, test_deleterow);
  tcase_add_test(tc_core, test_attachfig);
  tcase_add_test(tc_core, test_userInput_terminate);
  tcase_add_test(tc_core, test_userInput_start);
  tcase_add_test(tc_core, test_overflow);
  tcase_add_test(tc_core, test_pausepause);
  tcase_add_test(tc_core, test_terminate);
  tcase_add_test(tc_core, test_newgame);
  tcase_add_test(tc_core, test_procces_timer);
  tcase_add_test(tc_core, test_spawn);
  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int failed;
  Suite *s;
  SRunner *sr;

  s = tetris_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}