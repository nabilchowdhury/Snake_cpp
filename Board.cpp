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
    unsigned x = rand() % (maxHeight() - 2) + 1;
    unsigned y = rand() % (maxWidth() - 2) + 1;
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
    direction = tolower(direction);

    // Initialize to previous direction
    char prevDirection = m_snake.getDirection();
    int dx = Snake::DIRECTIONS[prevDirection][0];
    int dy = Snake::DIRECTIONS[prevDirection][1];
        
    // Check if move is valid i.e. snake doesn't try to move in opposite direction. Else, set to new direction.
    if (direction == 'h' && prevDirection == 'l') {
    } else if (direction == 'l' && prevDirection == 'h') {
    } else if (direction == 'j' && prevDirection == 'k') {
    } else if (direction == 'k' && prevDirection == 'j') {
    } else if (direction == prevDirection) {
    } else if (Snake::DIRECTIONS.find(direction) == Snake::DIRECTIONS.end()) {
    } else {
        dx = Snake::DIRECTIONS[direction][0];
        dy = Snake::DIRECTIONS[direction][1];
        m_snake.setDirection(direction);
    }

    auto curPos = m_snake.getCurrentPosition();
    unsigned newX = curPos.first + dx;
    unsigned newY = curPos.second + dy;

    if (newX <= 0) newX = maxHeight() - 2;
    else if (newX >= maxHeight() - 1) newX = 1;
    if (newY <= 0) newY = maxWidth() - 2;
    else if (newY >= maxWidth() - 1) newY = 1;

    bool grow = false;

    if (newX == m_food.first && newY == m_food.second) {
        grow = true;
        generateFood();
        // Max size reached, so we reset the snake
        if ((maxWidth() - 2) * (maxHeight() * 2) == m_snake.getSize() - 1) {
            m_snake.resetSnake(4);
        }
    }
    
    return m_snake.moveSnake(newX, newY, grow);
}

