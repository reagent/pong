#ifndef PLAYER_H
#define PLAYER_H

#include "structs.h"

Player * player_init(Field *field, int length);
void player_draw(Player *player, Field *field);
void player_move(Field *field, Player *player, int direction);

#endif

