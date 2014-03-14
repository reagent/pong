#include <stdlib.h>
#include <sys/time.h>
#include <ncurses.h>
#include <unistd.h>

#include "field.h"
#include "player.h"
#include "ball.h"
#include "game.h"

int main(int argc, char *argv[]) {
    struct timeval start_time;

    gettimeofday(&start_time, NULL);

    Game *game = game_init(start_time);

    while(1) { game_tick(game); }

    game_destroy(game);

    return 0;
}

