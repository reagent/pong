#ifndef GAME_H
#define GAME_H

#include "structs.h"

#define MICROSECONDS_PER_SECOND 1000000
#define BALL_DELAY 0.03

#define MOVE_UP   'j'
#define MOVE_DOWN 'k'

Game *game_init(struct timeval start_time);
void game_tick(Game *game);
void game_destroy(Game *game);

#endif

