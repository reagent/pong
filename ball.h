#ifndef BALL_H
#define BALL_H

#define BALL_MISS -1
#define BALL_MOVED 0
#define BALL_SCORE 1

#include "structs.h"

Ball *ball_init(Field *field);
void ball_draw(Ball *ball, Field *field);
void ball_reset(Ball *ball, Field *field);
int ball_move(Ball *ball, Field *field, Player *player);

#endif
