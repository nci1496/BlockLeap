#include "Rule.h"

bool Rule::isQueenMove(const Board& board, int x1, int y1, int x2, int y2)
{
    if (!board.inside(x2, y2)) return false;
    if (board.grid[x2][y2] != EMPTY) return false;

    int dx = x2 - x1;
    int dy = y2 - y1;
    if (dx == 0 && dy == 0) return false;

    if (dx != 0) dx /= abs(dx);
    if (dy != 0) dy /= abs(dy);

    int cx = x1 + dx;
    int cy = y1 + dy;

    while (cx != x2 || cy != y2)
    {
        if (board.grid[cx][cy] != EMPTY)
            return false;
        cx += dx;
        cy += dy;
    }

    return true;
}

bool Rule::canJump(const Board& board, bool redTurn, int x1, int y1, int x2, int y2)
{
    if (!board.inside(x2, y2)) return false;
    if (board.grid[x2][y2] != EMPTY) return false;

    int dx = x2 - x1;
    int dy = y2 - y1;

    // 必须刚好跳两格
    if (abs(dx) > 2 || abs(dy) > 2)
        return false;

    // 必须在同一直线（8方向）
    if (!(dx == 0 || dy == 0 || abs(dx) == abs(dy)))
        return false;

    // 必须刚好距离为2
    if (abs(dx) != 2 && abs(dy) != 2)
        return false;

    int mx = x1 + dx / 2;
    int my = y1 + dy / 2;

    Piece oppMain = redTurn ? BLUE : RED;
    Piece oppTrace = redTurn ? BLUE_TRACE : RED_TRACE;

    return (board.grid[mx][my] == oppMain || board.grid[mx][my] == oppTrace);
}

bool Rule::hasAnyJump(const Board& board,bool redTurn,sf::Vector2i pos)
{
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0) continue;

            int nx = pos.x + dx;
            int ny = pos.y + dy;

            while (board.inside(nx, ny))
            {
                if (Rule::canJump(board, redTurn, pos.x, pos.y, nx, ny))
                    return true;

                nx += dx;
                ny += dy;
            }
        }
    }
    return false;
}

bool Rule::hasAnyMove(const Board& board,bool redTurn,sf::Vector2i pos)
{
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0) continue;

            int nx = pos.x + dx;
            int ny = pos.y + dy;

            while (board.inside(nx, ny))
            {
                if (isQueenMove(board,pos.x, pos.y, nx, ny))
                    return true;

                if (canJump(board,redTurn,pos.x, pos.y, nx, ny))
                    return true;

                nx += dx;
                ny += dy;
            }
        }
    }

    return false;
}

std::vector<sf::Vector2i>Rule::generateMoves(const Board& board,bool redTurn,bool jumpOnly)
{
    std::vector<sf::Vector2i> moves;

    sf::Vector2i pos = redTurn ? board.redPos : board.bluePos;

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0) continue;

            int nx = pos.x + dx;
            int ny = pos.y + dy;

            while (board.inside(nx, ny))
            {
                if (jumpOnly)
                {
                    if (canJump(board, redTurn, pos.x, pos.y, nx, ny))
                        moves.push_back({ nx, ny });
                }
                else
                {
                    if (isQueenMove(board, pos.x, pos.y, nx, ny))
                        moves.push_back({ nx, ny });

                    if (canJump(board, redTurn, pos.x, pos.y, nx, ny))
                        moves.push_back({ nx, ny });
                }

                nx += dx;
                ny += dy;
            }
        }
    }

    return moves;
}