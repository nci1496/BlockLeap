#include "Game.h"
#include"Rule.h"
#include"Renderer.h"
#include <iostream>
using namespace std;

Game::Game() : window(sf::VideoMode(board.SIZE* board.CELL, board.SIZE* board.CELL+board.topOffset), "Chess Game")
{
    if (!font.loadFromFile("assets/arial.ttf"))
    {
        std::cout << "字体加载失败\n";
    }

    redTurn = true;
    selected = false;
    jumpMode = false;
    gameOver = false;
    redHP = 5;
    blueHP = 5;
}


void Game::updateHighlights()
{
    if (!selected)
    {
        highlights.clear();
        return;
    }

    highlights = Rule::generateMoves(board, redTurn, jumpMode);
}

void Game::performJump(sf::Vector2i& pos, int x2, int y2)
{
    int dx = x2 - pos.x;
    int dy = y2 - pos.y;

    if (dx != 0) dx /= abs(dx);
    if (dy != 0) dy /= abs(dy);

    int cx = pos.x + dx;
    int cy = pos.y + dy;

    Piece oppMain = redTurn ? BLUE : RED;

    while (cx != x2 || cy != y2)
    {
        if (board.grid[cx][cy] != EMPTY)
        {
            if (board.grid[cx][cy] == oppMain)
            {
                gameOver = true;
                winner = redTurn ? RED : BLUE;
            }

            board.grid[cx][cy] = EMPTY;
            break;
        }

        cx += dx;
        cy += dy;
    }

    board.grid[pos.x][pos.y] = redTurn ? RED_TRACE : BLUE_TRACE;

    pos.x = x2;
    pos.y = y2;

    board.grid[pos.x][pos.y] = redTurn ? RED : BLUE;
}

void Game::handleClick(int x, int y)
{
    sf::Vector2i& curPos = redTurn ? board.redPos : board.bluePos;
    Piece curPiece = redTurn ? RED : BLUE;

    
    if (!selected)
    {
        if (x == curPos.x && y == curPos.y)
        {
            selected = true;
        }
        else {
            selected = false;
        }
        updateHighlights();
        return;
    }

    // 连跳模式
    if (jumpMode)
    {
        if (Rule::canJump(board,redTurn,curPos.x, curPos.y, x, y))
        {
            performJump(curPos, x, y);
            if (!Rule::hasAnyJump(board, redTurn, curPos))
            {
                jumpMode = false;
                selected = false;
                redTurn = !redTurn;
            }
        }
        else
        {
            // 点击非法位置 → 结束回合
            jumpMode = false;
            selected = false;
            redTurn = !redTurn;
        }

        updateHighlights();
        return;
    }

    // 普通模式

    // 选择吃
    if (Rule::canJump(board,redTurn,curPos.x, curPos.y, x, y))
    {
        performJump(curPos, x, y);
        if (Rule::hasAnyJump(board,redTurn,curPos))
        {
            jumpMode = true;
        }
        else
        {
            jumpMode = false;
            selected = false;
            redTurn = !redTurn;
        }
        updateHighlights();
        return;
    }

    // 选择移动
    if (Rule::isQueenMove(board,curPos.x, curPos.y, x, y))
    {
        board.grid[curPos.x][curPos.y] = redTurn ? RED_TRACE : BLUE_TRACE;
        curPos.x = x;
        curPos.y = y;
        board.grid[x][y] = curPiece;

        selected = false;
        redTurn = !redTurn;
        updateHighlights();
        return;
    }

    // 非法点击取消选择
    selected = false;
}

void Game::update()
{
    sf::Vector2i pos = redTurn ? board.redPos : board.bluePos;

    if (!Rule::hasAnyMove(board,redTurn,pos))
    {
        gameOver = true;
        winner = redTurn ? BLUE : RED;
    }
}

void Game::render()
{
    RenderState state;
    state.board = &board;
    state.redTurn = redTurn;
    state.gameOver = gameOver;
    state.winner = winner;
    state.selected = selected;
    state.highlights = &highlights;
    state.redHP = redHP;
    state.blueHP = blueHP;
    state.font = &font;

    renderer.draw(window, state);

}

void Game::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!gameOver &&
                event.type == sf::Event::MouseButtonPressed)
            {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                if (mouseY < board.topOffset)
                {
                    continue;
                }

                int x = (mouseY-board.topOffset) / board.CELL;
                int y = mouseX / board.CELL;


                handleClick(x, y);
            }
        }

        if (!gameOver)
            update();

        render();
    }
}