#pragma once
#include <vector>
#include<SFML/System.hpp>

enum Piece {
    EMPTY,
    RED,
    BLUE,
    RED_TRACE,
    BLUE_TRACE
};

class Board
{
public:
    static const int SIZE = 8;
    static const int CELL = 80;

    int boardSize;        // ”√ªß—°‘Ò

    const int topOffset = 40;

    std::vector<std::vector<Piece>> grid;

    sf::Vector2i redPos;
    sf::Vector2i bluePos;

    Board();

    bool inside(int x, int y) const;
};

