#include <stdlib.h>
#include <ncurses.h>

#include "field.h"
#include "player.h"

Player * player_init(Field *field, int length) {
    int mid_x, mid_y;
    Player *player = malloc(sizeof(Player));

    field_get_midpoints(field, &mid_x, &mid_y);

    player->x      = 0;
    player->y      = mid_y - (length / 2);
    player->score  = 0;
    player->length = length;

    return player;
}

void player_draw(Player *player, Field *field) {
    int i = 0;
    int max_y = 0, max_x = 0;

    getmaxyx(field->game, max_y, max_x);

    // Make sure paddle doesn't go off screen
    if ((player->y + player->length) > max_y) {
        player->y = max_y - player->length;
    }

    // Draw player's paddle
    for (i = 0; i < player->length; i++) {
        mvwprintw(field->game, player->y + i, player->x, "|");
    }
}

void player_move(Field *field, Player *player, int direction) {
    int max_y = 0, max_x = 0;
    int next_y = player->y + direction;

    getmaxyx(field->game, max_y, max_x);

    if (next_y >= 0 && (next_y + player->length) <= max_y) {
        player->y = next_y;
    }
}

