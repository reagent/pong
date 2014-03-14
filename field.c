#include <ncurses.h>
#include <stdlib.h>

#include "player.h"
#include "field.h"

Field * field_init() {
    Field *field = malloc(sizeof(Field));
    int max_x = 0, max_y = 0;

    initscr();
    cbreak();
    noecho(); // Don't output the pressed key
    nodelay(stdscr, TRUE); // Don't block on getch() calls
    curs_set(FALSE); // Don't display the cursor on-screen

    getmaxyx(stdscr, max_y, max_x);

    field->container = stdscr;
    field->game      = newwin(max_y - 1, max_x, 0, 0);
    field->score     = newwin(1, max_x, max_y - 1, 0);

    return field;
}

void get_midpoints(WINDOW *window, int *mid_x, int *mid_y) {
    int max_x = 0, max_y = 0;

    getmaxyx(window, max_y, max_x);

    *mid_x = max_x / 2;
    *mid_y = max_y / 2;
}

void field_get_midpoints(Field *field, int *mid_x, int *mid_y) {
    // TODO: cache this on Field struct?
    get_midpoints(field->game, mid_x, mid_y);
}

void field_redraw(Field *field) {
    int container_x = 0,
        container_y = 0,
        game_x      = 0,
        game_y      = 0;

    getmaxyx(field->container, container_y, container_x);
    getmaxyx(field->game, game_y, game_x);

    // check if outer container size changed
    if (container_y != (game_y + 1) || container_x != game_x) {
        wresize(field->game, container_y - 1, container_x);
        wresize(field->score, 1, container_x);
        mvwin(field->score, 0, container_y - 1);
    }
}

void field_draw_score(Field *field, Player *player) {
    int mid_x, mid_y;

    get_midpoints(field->score, &mid_x, &mid_y);

    mvwprintw(field->score, 0, (mid_x - 2), "%04d", player->score);
}

void field_destroy(Field *field) {
    delwin(field->game);
    delwin(field->score);

    endwin();

    free(field);
}

