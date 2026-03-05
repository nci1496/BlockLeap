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

    selected = false;
    jumpMode = false;
    gameOver = false;
    
    currentPlayer = &redPlayer;
    opponentPlayer = &bluePlayer;
}

void Game::switchTurn()
{
    std::swap(currentPlayer, opponentPlayer);
}


void Game::updateHighlights()
{
    if (!selected)
    {
        highlights.clear();
        return;
    }

    highlights = Rule::generateMoves(board, currentPlayer->getSide(), jumpMode);
}

void Game::performJump(PlayerSide side,int x2, int y2)
{
    PlayerSide oppSide = getOpponent(side);
    sf::Vector2i curPos = board.getMainPos(side);
    int dx = x2 - curPos.x;
    int dy = y2 - curPos.y;

    if (dx != 0) dx /= abs(dx);
    if (dy != 0) dy /= abs(dy);

    int cx = curPos.x + dx;
    int cy = curPos.y + dy;

    Piece oppMain = board.getMainPiece(oppSide);



    while (cx != x2 || cy != y2)
    {
        if (board.grid[cx][cy] != EMPTY)
        {
            if (board.isMainOfSide(board.grid[cx][cy],oppSide))
            {
                //原本用的if(board.grid[cx][cy] == oppMain)
                //如果要吃的棋，是对面的主将，对面扣两滴
                opponentPlayer->damage(2);

            }
            if (board.isTraceOfSide(board.grid[cx][cy],oppSide)) {
                //如果要吃的棋，是对面的Trace，那就吃，
                board.grid[cx][cy] = EMPTY;
            }

            break;
        }

        cx += dx;
        cy += dy;
    }

    board.grid[curPos.x][curPos.y] = board.getTracePiece(side);

    sf::Vector2i newPos{ x2,y2 };
    board.setMainPos(side, newPos);
    board.grid[x2][y2] = board.getMainPiece(side);
}

void Game::handleClick(int x, int y)
{
    PlayerSide curSide=currentPlayer->getSide();//简化
    const sf::Vector2i& curPos = board.getMainPos(curSide);
    

    Piece curPiece = board.getMainPiece(curSide);
    
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
        if (Rule::canJump(board, curSide,curPos.x, curPos.y, x, y))
        {
            performJump(curSide, x, y);
            if (!Rule::hasAnyJump(board, curSide, curPos))
            {
                jumpMode = false;
                selected = false;
                switchTurn();
            }
        }
        else
        {
            // 点击非法位置 → 结束回合
            jumpMode = false;
            selected = false;
            switchTurn();
        }

        updateHighlights();
        return;
    }

    // 普通模式

    // 选择吃
    if (Rule::canJump(board,curSide,curPos.x, curPos.y, x, y))
    {
        performJump(curSide, x, y);
        if (Rule::hasAnyJump(board,curSide,curPos))
        {
            jumpMode = true;
        }
        else
        {
            jumpMode = false;
            selected = false;
            switchTurn();
        }
        updateHighlights();
        return;
    }

    // 选择移动
    if (Rule::isQueenMove(board,curPos.x, curPos.y, x, y))
    {
        board.grid[curPos.x][curPos.y] = board.getTracePiece(curSide);

        sf::Vector2i newPos{ x,y };
        board.setMainPos(curSide,newPos);
        board.grid[x][y] = curPiece;

        selected = false;
        switchTurn();
        updateHighlights();
        return;
    }

    // 非法点击取消选择
    selected = false;
}

void Game::update()
{
    sf::Vector2i pos = board.getMainPos(currentPlayer->getSide());


    if (!Rule::hasAnyMove(board,currentPlayer->getSide(), pos))
    {
        currentPlayer->damage(1);
        switchTurn();
    }
    if (redPlayer.getHP() == 0 || bluePlayer.getHP() == 0)
    {
        gameOver = true;
        if (redPlayer.getHP() == 0)
        {
            winner = BLUE_SIDE;
        }
    }
}

void Game::render()
{
    RenderState state;
    state.board = &board;
    state.redTurn = (currentPlayer->getSide()==RED_SIDE);
    state.gameOver = gameOver;
    state.winner = winner;
    state.selected = selected;
    state.highlights = &highlights;
    state.redHP = redPlayer.getHP();
    state.blueHP = bluePlayer.getHP();
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