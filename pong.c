#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 0;

    int maxX = 0,
        maxY = 0,
        curX = 0,
        curY = 0;

    int maxScore = 5;

    // TODO: randomize direction
    int xDirection = -1,
        yDirection = 1;

    int paddleSize = 10;

    int player1Score = 0,
        player2Score = 0;

    int player1PaddleY = 0,
        player2PaddleY = 0;

    int startX = 0,
        startY = 0;

    int ch = 0;

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE); // Don't block on getch() calls
    keypad(stdscr, FALSE);
    curs_set(FALSE);

    getmaxyx(stdscr, maxY, maxX);

    startX = maxX / 2;
    startY = maxY / 2;

    curX = startX;
    curY = startY;

    player1PaddleY = player2PaddleY = startY - (paddleSize / 2);

    while(1) {
        // game loop

        clear();
        // check for typed char

        if ((ch = getch()) != ERR) {
            if (ch == 'a' && player1PaddleY > 0) {
                // move player1 paddle up
                player1PaddleY--;
            }

            if (ch == 'z' && (player1PaddleY + paddleSize) < (maxY)) {
                // move player1 paddle down
                player1PaddleY++;
            }

            if (ch == 'l' && player2PaddleY > 0) {
                // move player2 paddle up
                player2PaddleY--;
            }

            if (ch == '.' && (player2PaddleY + paddleSize) < (maxY)) {
                // move player2 paddle down
                player2PaddleY++;
            }
        }

        // draw scoreboard
        mvprintw(0, 2, "Player 1: %02d, Player 2: %02d", player1Score, player2Score);

        // Draw player 1 paddle
        for (i = 0; i < paddleSize; i++) {
            mvprintw(player1PaddleY + i, 0, "|");
        }

        // Draw player 2 paddle
        for (i = 0; i < paddleSize; i++) {
            mvprintw(player2PaddleY + i, maxX - 1, "|");
        }

        // Draw the ball
        move(curY, curX);

        if ((curY > 0 && curY < maxY) || (curY == 0 && curX < 2 && curX > 28)) {
            printw("o");
        }

        refresh();

        // if the ball hits the top or bottom, bounce it
        if (curY >= (maxY - 1) || curY <= 0) {
            yDirection = yDirection * -1;
        }

        // if the ball hits a paddle, bounce it
        if ((curX + xDirection) <= 0) {
            if (curY >= player1PaddleY && curY <= player1PaddleY + paddleSize) {
                xDirection = xDirection * -1;
            } else {
                player2Score++;

                curX = startX;
                curY = startY;
            }
        }

        if ((curX + xDirection) >= (maxX - 1)) {
            if (curY >= player2PaddleY && curY <= player2PaddleY + paddleSize) {
                xDirection = xDirection * -1;
            } else {
                player1Score++;

                curX = startX;
                curY = startY;

            }

        }

        // if (player1Score > maxScore || player2Score > maxScore) {
        //     game_over();
        // }

        // if (curX >= (maxX - 1) || curX <= 0) {
        //     xDirection = xDirection * -1;
        // }


        curX += xDirection;
        curY += yDirection;

        usleep(50000);
    }

    endwin();

    return 0;
}
