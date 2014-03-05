#include <stdlib.h>
#include <time.h>
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

    int directions[] = {-1, 1};
    
    srand(time(NULL));

    // TODO: randomize direction
    int xDirection = directions[rand() % 2],
        yDirection = directions[rand() % 2];

    int paddleSize = 10;

    int player1Score = 0,
        player2Score = 0;

    int player1PaddleY = 0,
        player2PaddleY = 0;

    int startX = 0,
        startY = 0,
        fieldMaxX = 0,
        fieldMaxY = 0;

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

    WINDOW *gameField = newwin(maxY - 1, maxX, 0, 0);
    WINDOW *statusBar = newwin(1, maxX, maxY - 1, 0);

    player1PaddleY = player2PaddleY = startY - (paddleSize / 2);

    getmaxyx(gameField, fieldMaxY, fieldMaxX);

    while(1) {
        // game loop

        wclear(gameField);

        // check for typed char -- TODO: read in a keydown event
        if ((ch = getch()) != ERR) {
            if (ch == 'a' && player1PaddleY > 0) {
                // move player1 paddle up
                player1PaddleY--;
            }

            if (ch == 'z' && (player1PaddleY + paddleSize) < (fieldMaxY)) {
                // move player1 paddle down
                player1PaddleY++;
            }

            if (ch == 'l' && player2PaddleY > 0) {
                // move player2 paddle up
                player2PaddleY--;
            }

            if (ch == '.' && (player2PaddleY + paddleSize) < (fieldMaxY)) {
                // move player2 paddle down
                player2PaddleY++;
            }
        }

        // status bar
        wclear(statusBar);
        mvwprintw(statusBar, 0, maxX / 4, "%02d", player1Score);
        mvwprintw(statusBar, 0, (maxX / 4) * 3, "%02d", player2Score);
        wrefresh(statusBar);

        // Draw player 1 paddle
        for (i = 0; i < paddleSize; i++) {
            mvwprintw(gameField, player1PaddleY + i, 0, "|");
        }

        // Draw player 2 paddle
        for (i = 0; i < paddleSize; i++) {
            mvwprintw(gameField, player2PaddleY + i, fieldMaxX - 1, "|");
        }

        if (player1Score == maxScore || player2Score == maxScore) {
            mvwprintw(gameField, fieldMaxY / 2, fieldMaxX / 2, "Game Over.");
            wrefresh(gameField);

            sleep(2);

            curX = startX;
            curY = startY;

            player1Score = 0;
            player2Score = 0;

            player1PaddleY = player2PaddleY = startY - (paddleSize / 2);
        }


        // Draw the ball
        mvwprintw(gameField, curY, curX, "o");
        wrefresh(gameField);

        // if the ball hits the top or bottom, bounce it
        if (curY >= (fieldMaxY - 1) || curY <= 0) {
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
                
                xDirection = directions[rand() % 2],
                yDirection = directions[rand() % 2];
            }
        }

        if ((curX + xDirection) >= (fieldMaxX - 1)) {
            if (curY >= player2PaddleY && curY <= player2PaddleY + paddleSize) {
                xDirection = xDirection * -1;
            } else {
                player1Score++;

                curX = startX;
                curY = startY;
                
                xDirection = directions[rand() % 2],
                yDirection = directions[rand() % 2];
            }

        }

        curX += xDirection;
        curY += yDirection;

        usleep(45000);
    }

    sleep(1);

    delwin(gameField);
    delwin(statusBar);

    endwin();

    return 0;
}
