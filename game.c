#include <sys/time.h>
#include <ncurses.h>
#include <stdlib.h>

#include "field.h"
#include "player.h"
#include "ball.h"

#include "game.h"

long elapsed_since(struct timeval *time) {
  struct timeval now;

  gettimeofday(&now, NULL);

  return ((now.tv_sec   * MICROSECONDS_PER_SECOND) + now.tv_usec) -
         ((time->tv_sec * MICROSECONDS_PER_SECOND) + time->tv_usec);

}

Game * game_init(struct timeval start_time) {
    Game *game = malloc(sizeof(Game));

    Field  *field  = field_init();
    Player *player = player_init(field, 10);
    Ball   *ball   = ball_init(field);

    game->field      = field;
    game->player     = player;
    game->ball       = ball;
    game->start_time = start_time;

    return game;
}

void game_tick(Game *game) {
    int ch = 0, move_result = BALL_MOVED;

    long elapsed = elapsed_since(&game->start_time);
    static long last_event = 0;

    if ((elapsed - last_event) >= (BALL_DELAY * MICROSECONDS_PER_SECOND)) {
        move_result = ball_move(game->ball, game->field, game->player);

        if (move_result == BALL_SCORE) {
          game->player->score += 1;
        } else if (move_result == BALL_MISS) {
          game->player->score = 0;
          ball_reset(game->ball, game->field);
        }

        last_event = elapsed;
    }

    if ((ch = getch()) != ERR) {
        if (ch == MOVE_UP) {
            player_move(game->field, game->player, -1);
        }

        if (ch == MOVE_DOWN) {
            player_move(game->field, game->player, 1);
        }
    }

    // field_refresh(game->field);

    field_redraw(game->field);

    wclear(game->field->game);

    field_draw_score(game->field, game->player);
    wrefresh(game->field->score);

    player_draw(game->player, game->field);
    ball_draw(game->ball, game->field);

    wrefresh(game->field->game);
}

void game_destroy(Game *game) {
    field_destroy(game->field);

    free(game->player);
    free(game->ball);

    free(game);
}

