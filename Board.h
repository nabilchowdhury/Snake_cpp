#ifndef _BOARD_H
#define _BOARD_H
#include "Snake.h"

class Board {
private:
    unsigned m_WIDTH, m_HEIGHT;
    Snake& m_snake;
    std::pair<unsigned, unsigned> m_food;

public:
    Board() = delete;
    explicit Board(unsigned W, unsigned H, Snake& snake);
    std::pair<unsigned, unsigned> generateFood();
    unsigned maxWidth() const;
    unsigned maxHeight() const;
    void display();
    SnakeStatus moveSnake(char direction);
};
#endif //_BOARD_H
