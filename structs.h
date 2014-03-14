#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Player {
    int x;
    int y;
    int length;
    int score;
} Player;

typedef struct Field {
    WINDOW *container;
    WINDOW *game;
    WINDOW *score;
} Field;

typedef struct Ball {
    int x;
    int y;
    int x_direction;
    int y_direction;
} Ball;

typedef struct Game {
    Player *player;
    Ball   *ball;
    Field  *field;
    struct timeval start_time;
} Game;

#endif

