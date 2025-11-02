#ifndef INTERFACE_H
#define INTERFACE_H

#include "../../brick_game/tetris/game_info.h"

#define BOARD 2
#define FIELD_NEXT 4

void render_basic(GameInfo_t info, WINDOW *win, WINDOW *win_info,
                  WINDOW *next_fig);
void render(GameInfo_t info);
void terminate_game();

#endif