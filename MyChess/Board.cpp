#include "Board.h"
const sf::Vector2i& Board::getMainPos(PlayerSide side)const
{
    return(side == RED_SIDE) ? redPos : bluePos;
}

Piece Board::getMainPiece(PlayerSide side) const
{
    return (side == RED_SIDE) ? RED : BLUE;
}

Piece Board::getTracePiece(PlayerSide side) const
{
    return (side == RED_SIDE) ? RED_TRACE : BLUE_TRACE;
}

bool Board::isMainOfSide(Piece p, PlayerSide side) const
{
    return (side == RED_SIDE && p == RED) ||(side == BLUE_SIDE && p == BLUE);
}

bool Board::isTraceOfSide(Piece p, PlayerSide side) const
{
    return (side == RED_SIDE && p == RED_TRACE) || (side == BLUE_SIDE && p == BLUE_TRACE);
}


void Board::setMainPos(PlayerSide side, const sf::Vector2i& newPos)
{
    if (side == RED_SIDE)
    {
        redPos = newPos;
    }
    else
    {
        bluePos = newPos;
    }
}

Board::Board()
{
    grid.resize(SIZE, std::vector<Piece>(SIZE, EMPTY));

    redPos = { 0, 0 };
    bluePos = { SIZE - 1, SIZE - 1 };

    grid[redPos.x][redPos.y] = RED;
    grid[bluePos.x][bluePos.y] = BLUE;
}

bool Board::inside(int x, int y) const
{
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}