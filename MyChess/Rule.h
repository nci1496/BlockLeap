#pragma once
#include"Board.h"

class Rule
{
public:
    static bool isQueenMove(const Board& board,int x1, int y1,int x2, int y2);

    static bool canJump(const Board& board,bool redTurn,int x1, int y1,int x2, int y2);
    static bool hasAnyJump(const Board& board, bool redTurn, sf::Vector2i pos);

    static bool hasAnyMove(const Board& board,bool redTurn, sf::Vector2i pos);

    static std::vector<sf::Vector2i>generateMoves(const Board& board,bool redTurn,bool jumpOnly);
};

