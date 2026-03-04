#include "Board.h"
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