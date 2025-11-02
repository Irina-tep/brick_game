#include "interface.h"

void terminate_game() {
  endwin();
  exit(0);
}

void render(GameInfo_t info) {
  refresh();
  WINDOW *win = newwin(BOARD + FIELD_H, BOARD + FIELD_W * 3, 0, 0);
  WINDOW *win_info = newwin(22, 15, 0, 32 + 1);
  WINDOW *next_fig = newwin(6, 10, 15, 35);

  box(win, 0, 0);
  box(win_info, 0, 0);
  box(next_fig, 0, 0);
  mvwprintw(win_info, 1, 2, "LEVEL");
  mvwprintw(win_info, 4, 2, "SCORE");
  mvwprintw(win_info, 7, 2, "HIGH SCORE");
  mvwprintw(win_info, 10, 2, "SPEED");
  mvwprintw(win_info, 13, 2, "NEXT");
  wrefresh(win);
  wrefresh(win_info);
  if (info.pause == GameStart) {
    mvwprintw(win, 3, 6,
              "PRESS "
              "S"
              " TO START");
  }

  else if (info.pause == YouLost) {
    mvwprintw(win, 3, 9, "GAME OVER");
    mvwprintw(win, 6, 7,
              "PRESS "
              "S"
              " TO START");
  } else {
    render_basic(info, win, win_info, next_fig);
    if (info.pause == GamePause) {
      mvwprintw(win, 3, 6, "PAUSE");
    }
  }

  wrefresh(win);
  wrefresh(win_info);
  wrefresh(next_fig);
  for (int i = 0; i < FIELD_H; i++) {
    free(info.field[i]);
  }
  free(info.field);

  for (int i = 0; i < FIELD_NEXT; i++) {
    free(info.next[i]);
  }
  free(info.next);
  delwin(next_fig);
  delwin(win);
  delwin(win_info);
}

void render_basic(GameInfo_t info, WINDOW *win, WINDOW *win_info,
                  WINDOW *next_fig) {
  for (int i = 0; i < FIELD_H; i++) {
    for (int j = 0; j < FIELD_W; j++) {
      if (info.field[i][j] == 1) {
        mvwaddch(win, i + 1, 3 * j + 1, ACS_CKBOARD);
        mvwaddch(win, i + 1, 3 * j + 2, ACS_CKBOARD);
        mvwaddch(win, i + 1, 3 * j + 3, ACS_CKBOARD);
      } else {
        mvwprintw(win, i + 1, 3 * j + 1, "   ");
      }
    }
  }
  mvwprintw(win_info, 2, 2, "%d", info.level);
  mvwprintw(win_info, 5, 2, "%d", info.score);
  mvwprintw(win_info, 8, 2, "%d", info.high_score);
  mvwprintw(win_info, 11, 2, "%d", info.speed);

  for (int i = 0; i < FIELD_NEXT; i++) {
    for (int j = 0; j < FIELD_NEXT; j++) {
      if (info.next[i][j] == 1) {
        mvwaddch(next_fig, i + 1, 2 * j + 1, ACS_CKBOARD);
        mvwaddch(next_fig, i + 1, 2 * j + 2, ACS_CKBOARD);
      } else
        mvwprintw(next_fig, i + 1, 2 * j + 1, "  ");
    }
  }
}
