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

bool Rule::canJump(const Board& board, PlayerSide side, int x1, int y1, int x2, int y2)
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

    PlayerSide oppSide = getOpponent(side);

    Piece oppMain = board.getMainPiece(oppSide);
    Piece oppTrace = board.getTracePiece(oppSide);

    Piece mid = board.grid[mx][my];
    //如果这个中间的棋子，是对方的主将，或者是对方的轨迹，就能跳
    return (board.isMainOfSide(mid,oppSide) || board.isTraceOfSide(mid,oppSide));
}

bool Rule::hasAnyJump(const Board& board, PlayerSide side,sf::Vector2i pos)
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
                if (Rule::canJump(board, side, pos.x, pos.y, nx, ny))
                    return true;

                nx += dx;
                ny += dy;
            }
        }
    }
    return false;
}

bool Rule::hasAnyMove(const Board& board, PlayerSide side,sf::Vector2i pos)
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

                if (canJump(board,side,pos.x, pos.y, nx, ny))
                    return true;

                nx += dx;
                ny += dy;
            }
        }
    }

    return false;
}

std::vector<sf::Vector2i>Rule::generateMoves(const Board& board, PlayerSide side,bool jumpOnly)
{
    std::vector<sf::Vector2i> moves;

    sf::Vector2i pos = board.getMainPos(side);


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
                    if (canJump(board, side, pos.x, pos.y, nx, ny))
                        moves.push_back({ nx, ny });
                }
                else
                {
                    if (isQueenMove(board, pos.x, pos.y, nx, ny))
                        moves.push_back({ nx, ny });

                    if (canJump(board, side, pos.x, pos.y, nx, ny))
                        moves.push_back({ nx, ny });
                }

                nx += dx;
                ny += dy;
            }
        }
    }

    return moves;
}