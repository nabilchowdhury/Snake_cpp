#include "Board.h"
#include "Snake.h"

#include <ncurses.h>

#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>


using namespace std;
using namespace chrono;

int kbhit() {
    int ch = getch();
    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char *argv[]) {
    // Check args
    if (argc < 3) {
        cerr << "Usage: ./snake width height\n";
        return 1;
    }

    // Parse args
    int width = stoi(argv[1]);
    int height = stoi(argv[2]);

    // This weird string resizes the terminal!
    cout << "\e[8;" << height + 2 << ";" << width + 4 << "t";

    // Snake Game
    // First we instatiate a Snake
    Snake snake(height / 2, width / 2);

    // Then we instantiate a board and generate food
    Board board(width, height, snake);

    // Key Press setup
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    char ch = '.';
    SnakeStatus status;

    while (true) {
        if (kbhit()) {
            ch = (char)getch();
        }
        if (ch == 'q') {// quit
            return 0;
        }
        board.moveSnake(ch);
        refresh();
        board.display();
        this_thread::sleep_for(milliseconds(200 - snake.getScore()));
    }
    return 0;
}
