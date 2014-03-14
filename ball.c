#include <ncurses.h>
#include <stdlib.h>

#include "field.h"
#include "ball.h"

Ball *ball_init(Field *field) {
    Ball *ball = malloc(sizeof(Ball));

    ball_reset(ball, field);

    return ball;
}

void ball_draw(Ball *ball, Field *field) {
    mvwprintw(field->game, ball->y, ball->x, "o");
}

void ball_reset(Ball *ball, Field *field) {
    int mid_x, mid_y;

    field_get_midpoints(field, &mid_x, &mid_y);

    ball->x = mid_x;
    ball->y = mid_y;

    ball->x_direction = 2;
    ball->y_direction = 1;
}

int ball_move(Ball *ball, Field *field, Player *player) {
    int max_x  = 0,
        max_y  = 0,
        next_x = ball->x + ball->x_direction,
        next_y = ball->y + ball->y_direction;

    int result = BALL_MOVED;

    int player_y1 = player->y,
        player_y2 = player->y + player->length;

    // TODO: Cache this on Field?
    getmaxyx(field->game, max_y, max_x);

    if (next_y <= 0 || next_y >= max_y) {
        ball->y_direction *= -1;
    } else if (next_x >= max_x) {
        ball->x_direction *= -1;
    } else if (next_x <= 0) {

        if (next_y >= player_y1 && next_y <= player_y2) {
            ball->x_direction *= -1;
            result = BALL_SCORE;
        } else {
            result = BALL_MISS;
        }

    }

    ball->x += ball->x_direction;
    ball->y += ball->y_direction;

    return result;
}

