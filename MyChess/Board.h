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

    const int HeartStarLeft_x=10;//左边的用户心的位置朝x轴正方向（水平）移动10
    const int HeartStarRight_x = 300;//右边的用户心的位置朝x轴正方向（水平）移动300
    const int HeartStarY = 50;//心的位置y正方向移动...

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

