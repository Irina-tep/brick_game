#include "tetris_fsm.h"
#include "user_input.h"

int main() {
  initscr();
  noecho();
  curs_set(0);
  cbreak();
  keypad(stdscr, TRUE);
  init_state();
  render(updateCurrentState());
  while (true) {
    State_t *state = getCurrentState();

    if (state->status == Initial || state->status == Moving) {
      updateUserAction();
    } else {
      if (state->status == Spawn) {
        spawn_new_figure();
      } else if (state->status == Shifting) {
        shift_figure();
      } else if (state->status == Attaching) {
        attach_figure();
      } else if (state->status == GameOver) {
        game_over();
      }
    }

    render(updateCurrentState());
  }
  return 0;
}
