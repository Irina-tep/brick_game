#include "user_input.h"

// LCOV_EXCL_START
void updateUserAction()
{
  State_t *state = getCurrentState();
  unsigned long long left_time = procces_timer();
  timeout(left_time);
  int input = getch();
  if (input == ESCAPE)
  {
    userInput(Terminate, false);
    terminate_game();
  }
  else if (state->status == Initial)
  {
    if (input == START_BUTTON)
    {
      userInput(Start, false);
    }
  }
  else
  {
    if (input == ENTER_KEY || input == PAUSE_BUTTON)
    {
      userInput(Pause, false);
      render(updateCurrentState());
      int inpt;
      int pressed = 1;
      while (pressed)
      {
        inpt = getch();
        if (inpt == ESCAPE)
        {
          userInput(Terminate, false);
          terminate_game();
          pressed = 0;
        }
        else if (inpt == PAUSE_BUTTON || inpt == ENTER_KEY)
        {
          userInput(Pause, false);
          pressed = 0;
        }
      }
    }
    else if (input == KEY_LEFT)
    {
      userInput(Left, false);
    }
    else if (input == KEY_RIGHT)
    {
      userInput(Right, false);
    }
    else if ((input == KEY_DOWN))
    {
      userInput(Down, false);
    }
    else if (input == ACTION_BUTTON)
    {
      userInput(Action, false);
    }
    else if (input == KEY_UP)
    {
      userInput(Up, false);
    }
    else if (input == ERR && state->status == Moving)
    {
      state->status = Shifting;
    }
  }
}
// LCOV_EXCL_STOP

void userInput(UserAction_t action, bool hold)
{
  if (!hold)
  {
    switch (action)
    {
    case Left:
      move_left();
      break;
    case Right:
      move_right();
      break;
    case Down:
      move_down();
      break;
    case Up:
      hard_drop();
      break;
    case Action:
      rotate_figure();
      break;
    case Start:
      start_game();
      break;
    case Pause:
      pause_game();
      break;
    case Terminate:
      game_over();
      break;
    }
  }
}

void start_game()
{
  State_t *state = getCurrentState();
  state->status = Spawn;
}

int figure_attached()
{
  State_t *state = getCurrentState();
  int attached = 0;
  for (int i = 0; i < state->size_figure; i++)
  {
    for (int j = 0; j < state->size_figure; j++)
    {
      if (state->figure[i][j] == 1)
      {
        int new_coord_x = state->coord_x + 1 + i;
        int new_coord_y = state->coord_y + j;
        if ((new_coord_x >= FIELD_H) ||
            ((new_coord_x >= 0) && (new_coord_y < FIELD_W) &&
             (state->field[new_coord_x][new_coord_y] == 1)))
          attached = 1;
      }
    }
  }
  return attached;
}

void move_left()
{
  State_t *state = getCurrentState();
  int move_is_possible = 1;
  for (int i = 0; i < state->size_figure; i++)
  {
    for (int j = 0; j < state->size_figure; j++)
    {
      int new_coord_x = state->coord_x + i;
      int new_coord_y = state->coord_y - 1 + j;
      if ((state->figure[i][j] == 1) && (new_coord_y < 0))
      {
        move_is_possible = 0;
      }
      else if ((new_coord_y >= 0) && (new_coord_x >= 0) &&
               (new_coord_y < FIELD_W) && new_coord_x < FIELD_H)
      {
        if ((state->figure[i][j] + state->field[new_coord_x][new_coord_y]) == 2)
          move_is_possible = 0;
      }
    }
  }
  if (move_is_possible == 1)
  {
    (state->coord_y)--;
  }
  state->status = Moving;
}

void move_right()
{
  State_t *state = getCurrentState();
  int move_is_possible = 1;
  for (int i = 0; i < state->size_figure; i++)
  {
    for (int j = 0; j < state->size_figure; j++)
    {
      int new_coord_x = state->coord_x + i;
      int new_coord_y = state->coord_y + 1 + j;
      if ((state->figure[i][j] == 1) && (new_coord_y >= FIELD_W))
      {
        move_is_possible = 0;
      }
      else if ((new_coord_y < FIELD_W) && (new_coord_x >= 0) && new_coord_x < FIELD_H)
      {
        if ((state->figure[i][j] + state->field[new_coord_x][new_coord_y]) == 2)
          move_is_possible = 0;
      }
    }
  }
  if (move_is_possible == 1)
  {
    (state->coord_y)++;
  }

  state->status = Moving;
}

void move_down()
{
  State_t *state = getCurrentState();
  if (figure_attached() == 0)
  {
    state->coord_x++;
    state->start_time = current_timeMs();
  }

  if (figure_attached() == 1)
  {
    state->status = Attaching;
  }
  else
  {
    state->status = Moving;
  }
}

void rotate_figure()
{
  State_t *state = getCurrentState();
  int **new_figure = create_matrix(state->size_figure, state->size_figure);
  rotate(new_figure, state->figure, state->size_figure);
  if (rotate_is_possible(new_figure) == 1)
  {
    remove_matrix(state->figure, state->size_figure);
    state->figure = new_figure;
  }
  else
  {
    remove_matrix(new_figure, state->size_figure);
  }
  int attached = figure_attached();
  if (attached == 0)
  {
    state->status = Moving;
  }
  else
  {
    state->status = Attaching;
  }
}

int rotate_is_possible(int **new_figure)
{
  State_t *state = getCurrentState();
  int is_possible = 1;
  for (int i = 0; i < state->size_figure; i++)
  {
    for (int j = 0; j < state->size_figure; j++)
    {
      int new_coord_x = state->coord_x + i;
      int new_coord_y = state->coord_y + j;

      if (new_coord_y < 0 || new_coord_y >= FIELD_W || new_coord_x < 0 ||
          new_coord_y >= FIELD_H)
      {
        is_possible = 0;
      }
      else if ((new_figure[i][j] + state->field[new_coord_x][new_coord_y]) ==
               2)
      {
        is_possible = 0;
      }
    }
  }
  return is_possible;
}

void pause_game()
{
  State_t *state = getCurrentState();
  if (state->pause == 0)
  {
    state->pause = 1;
    unsigned long long elapsedTime = current_timeMs() - state->start_time;
    if (elapsedTime >= state->left_time)
    {
      state->left_time = 0;
    }
    else
    {
      state->left_time = elapsedTime;
    }
  }
  else
  {
    state->pause = 0;
    state->start_time = current_timeMs();
  }
}

void hard_drop()
{
  State_t *state = getCurrentState();
  while (figure_attached() == 0)
  {
    (state->coord_x)++;
    render(updateCurrentState());
    sleep(0.001);
  }
  state->status = Attaching;
}