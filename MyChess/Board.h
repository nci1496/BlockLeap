#pragma once
#include<SFML/System.hpp>
#include"Types.h"

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

    int boardSize;        // 用户选择

    const int topOffset = 100;

    std::vector<std::vector<Piece>> grid;

    sf::Vector2i redPos;
    sf::Vector2i bluePos;

    const sf::Vector2i& getMainPos(PlayerSide side) const;
    Piece getMainPiece(PlayerSide side) const;
    Piece getTracePiece(PlayerSide side) const;
    bool isMainOfSide(Piece p, PlayerSide side) const;
    bool isTraceOfSide(Piece p, PlayerSide side) const;

    //修改
    void setMainPos(PlayerSide side, const sf::Vector2i& newPos);
    Board();

    bool inside(int x, int y) const;
};

