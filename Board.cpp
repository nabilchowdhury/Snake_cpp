#include "Board.h"
#include "Snake.h"

#include <ncurses.h>

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Board::Board(unsigned W, unsigned H, Snake& snake):
    m_WIDTH(W),
    m_HEIGHT(H),
    m_snake(snake) 
{
    srand(time(NULL));
    generateFood();
}

unsigned Board::maxWidth() const {
    return m_WIDTH;
}

unsigned Board::maxHeight()const {
    return m_HEIGHT;
}

pair<unsigned, unsigned> Board::generateFood() {
    unsigned x = rand() % (maxHeight() - 1) + 1;
    unsigned y = rand() % (maxWidth() - 1) + 1;
    m_food = {x, y};
    return m_food;
}

void Board::display() {
    stringstream ss;
    for (unsigned i = 0; i < maxHeight(); ++i) {
        for (unsigned j = 0; j < maxWidth(); ++j) {
            if (i == 0 || i == maxHeight() - 1 || j == 0 || j == maxWidth() - 1) {
                ss << '#';
            } else if (m_food.first == i && m_food.second == j) {
                ss << '@';
            } else if (m_snake.isSnakeAt(i, j)) {
                ss << '*';
            } else {
                ss << ' ';
            }
        }
        ss << '\n';
    }
    ss << "Score: " << m_snake.getScore() << '\n';
    printw("%s", ss.str().data());
}

SnakeStatus Board::moveSnake(char direction) {
    int dx = Snake::DIRECTIONS[direction][0];
    int dy = Snake::DIRECTIONS[direction][1];

    // Check if move is valid. If not, correct dx, dy
    char prevDirection = m_snake.getDirection();
    if (direction == 'h' && prevDirection == 'l') {
        dx = Snake::DIRECTIONS['l'][0];
        dy = Snake::DIRECTIONS['l'][1];
    } else if (direction == 'l' && prevDirection == 'h') {
        dx = Snake::DIRECTIONS['h'][0];
        dy = Snake::DIRECTIONS['h'][1];
    } else if (direction == 'j' && prevDirection == 'k') {
        dx = Snake::DIRECTIONS['k'][0];
        dy = Snake::DIRECTIONS['k'][1];
    } else if (direction == 'k' && prevDirection == 'j') {
        dx = Snake::DIRECTIONS['j'][0];
        dy = Snake::DIRECTIONS['j'][1];
    }

    auto curPos = m_snake.getCurrentPosition();
    unsigned newX = curPos.first + dx;
    unsigned newY = curPos.second + dy;

    if (newX <= 0) newX = maxHeight() - 1;
    else if (newX >= maxHeight() - 1) newX = 0;
    if (newY <= 0) newY = maxWidth() - 1;
    else if (newY >= maxWidth() - 1) newY = 0;

    bool grow = false;

    if (newX == m_food.first && newY == m_food.second) {
        grow = true;
        generateFood();
    }
    
    m_snake.setDirection(direction);
    return m_snake.moveSnake(newX, newY, grow);
}

