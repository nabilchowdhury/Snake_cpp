#ifndef _SNAKE_H
#define _SNAKE_H
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

enum class SnakeStatus {
    ISOK,
    DEAD,
    INIT
};

class Snake {
public:
    static unordered_map<char, vector<int>> DIRECTIONS;

private:
    unsigned m_score;
    list<pair<unsigned, unsigned>> m_coordinates;
    unordered_map<unsigned, unordered_set<unsigned>> m_lookup;
    char m_direction;

public:
    Snake() = delete;
    explicit Snake(unsigned x, unsigned y, char direction);
    SnakeStatus moveSnake(unsigned x, unsigned y, bool grow=false);
    void resetSnake(unsigned length);
    unsigned getScore() const;
    pair<unsigned, unsigned> getCurrentPosition() const;
    bool isSnakeAt(unsigned x, unsigned y);
    void setDirection(char direction);
    char getDirection() const;
};
#endif //_SNAKE_H
