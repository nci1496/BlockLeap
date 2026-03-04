#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : window(sf::VideoMode(SIZE* CELL, SIZE* CELL), "Chess Game")
{

    if (!font.loadFromFile("assets/arial.ttf"))
    {
        std::cout << "字体加载失败\n";
    }

    board.resize(SIZE, vector<Piece>(SIZE, EMPTY));

    redPos = { 0, 0 };
    bluePos = { SIZE - 1, SIZE - 1 };

    board[redPos.x][redPos.y] = RED;
    board[bluePos.x][bluePos.y] = BLUE;

    redTurn = true;
    selected = false;
    jumpMode = false;
    gameOver = false;

    pieceSelected = false;
}

bool Game::inside(int x, int y)
{
    return x >= 0 && x < SIZE && y >= 0 && y < SIZE;
}

bool Game::isQueenMove(int x1, int y1, int x2, int y2)
{
    if (!inside(x2, y2)) return false;
    if (board[x2][y2] != EMPTY) return false;

    int dx = x2 - x1;
    int dy = y2 - y1;
    if (dx == 0 && dy == 0) return false;

    if (dx != 0) dx /= abs(dx);
    if (dy != 0) dy /= abs(dy);

    int cx = x1 + dx;
    int cy = y1 + dy;

    while (cx != x2 || cy != y2)
    {
        if (board[cx][cy] != EMPTY)
            return false;
        cx += dx;
        cy += dy;
    }

    return true;
}

bool Game::canJump(int x, int y, int x2, int y2)
{
    if (!inside(x2, y2)) return false;
    if (board[x2][y2] != EMPTY) return false;

    int dx = x2 - x;
    int dy = y2 - y;

    // 必须同一直线（八方向）
    if (dx != 0) dx /= abs(dx);
    if (dy != 0) dy /= abs(dy);

    int cx = x + dx;
    int cy = y + dy;

    bool foundEnemy = false;

    while (inside(cx, cy))
    {
        if (cx == x2 && cy == y2)
            break;

        if (board[cx][cy] != EMPTY)
        {
            if (foundEnemy)
                return false; // 中间超过一个棋子

            Piece oppMain = redTurn ? BLUE : RED;
            Piece oppTrace = redTurn ? BLUE_TRACE : RED_TRACE;

            if (board[cx][cy] == oppMain || board[cx][cy] == oppTrace)
            {
                foundEnemy = true;
            }
            else
            {
                return false; // 是自己棋
            }
        }

        cx += dx;
        cy += dy;
    }

    return foundEnemy;
}

bool Game::hasAnyJump(sf::Vector2i pos)
{
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0) continue;

            int nx = pos.x + dx;
            int ny = pos.y + dy;

            while (inside(nx, ny))
            {
                if (canJump(pos.x, pos.y, nx, ny))
                    return true;

                nx += dx;
                ny += dy;
            }
        }
    }
    return false;
}

void Game::calculateHighlights()
{
    highlights.clear();

    sf::Vector2i pos = redTurn ? redPos : bluePos;

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0) continue;

            int nx = pos.x + dx;
            int ny = pos.y + dy;

            while (inside(nx, ny))
            {
                if (jumpMode)
                {
                    if (canJump(pos.x, pos.y, nx, ny))
                        highlights.push_back({ nx,ny });
                }
                else
                {
                    if (isQueenMove(pos.x, pos.y, nx, ny))
                        highlights.push_back({ nx,ny });
                    if (canJump(pos.x, pos.y, nx, ny))
                        highlights.push_back({ nx,ny });
                }

                nx += dx;
                ny += dy;
            }
        }
    }
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
        if (board[cx][cy] != EMPTY)
        {
            if (board[cx][cy] == oppMain)
            {
                gameOver = true;
                winner = redTurn ? RED : BLUE;
            }

            board[cx][cy] = EMPTY;
            break;
        }

        cx += dx;
        cy += dy;
    }

    board[pos.x][pos.y] = redTurn ? RED_TRACE : BLUE_TRACE;

    pos.x = x2;
    pos.y = y2;

    board[pos.x][pos.y] = redTurn ? RED : BLUE;
}

void Game::handleClick(int x, int y)
{
    sf::Vector2i& curPos = redTurn ? redPos : bluePos;
    Piece curPiece = redTurn ? RED : BLUE;

    if (!selected)
    {
        if (x == curPos.x && y == curPos.y)
        {
            selected = true;
            pieceSelected = true;
        }
        return;
    }

    // 连跳模式
    if (jumpMode)
    {
        if (canJump(curPos.x, curPos.y, x, y))
        {
            performJump(curPos, x, y);
        }
        else
        {
            // 点击非法位置 → 结束回合
            jumpMode = false;
            selected = false;
            pieceSelected = false;
            redTurn = !redTurn;


        }
        return;
    }

    // 普通模式

    // 选择吃
    if (canJump(curPos.x, curPos.y, x, y))
    {
        performJump(curPos, x, y);
        if (hasAnyJump(curPos))
        {
            jumpMode = true;
        }
        else
        {
            jumpMode = false;
            selected = false;
            pieceSelected = false;
            redTurn = !redTurn;
        }
        return;
    }

    // 选择移动
    if (isQueenMove(curPos.x, curPos.y, x, y))
    {
        board[curPos.x][curPos.y] = redTurn ? RED_TRACE : BLUE_TRACE;
        curPos.x = x;
        curPos.y = y;
        board[x][y] = curPiece;

        selected = false;
        redTurn = !redTurn;
        return;
    }

    // 非法点击取消选择
    selected = false;
}

void Game::update()
{
    sf::Vector2i pos = redTurn ? redPos : bluePos;

    bool hasMove = false;

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0) continue;

            int nx = pos.x + dx;
            int ny = pos.y + dy;

            while (inside(nx, ny) && board[nx][ny] == EMPTY)
            {
                hasMove = true;
                break;
            }
        }
    }

    if (!hasMove)
    {

        gameOver = true;
        winner = redTurn ?  BLUE: RED;
        //cout << (redTurn ? "红方" : "蓝方") << " 无路可走，判负\n";
        //exit(0);
    }
}

void Game::render()
{
    if (!gameOver)
        window.setTitle(redTurn ? "Red Turn" : "Blue Turn");
    else
        window.setTitle("Game Over");

    window.clear();



    if (gameOver)//这样处理，确保游戏结束后，不屏闪,（但还是状态转化更好）
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::Yellow);
        text.setString(winner == RED ? "RED WINS" : "BLUE WINS");
        text.setPosition(150, 300);

        window.draw(text);
        window.display();
        return;
    }
    else{

        calculateHighlights();

        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                sf::RectangleShape cell(sf::Vector2f(CELL, CELL));
                cell.setPosition(j * CELL, i * CELL);

                if ((i + j) % 2 == 0)
                    cell.setFillColor(sf::Color(180, 180, 180));
                else
                    cell.setFillColor(sf::Color(120, 120, 120));

                window.draw(cell);





                // 画高亮
                for (auto& h : highlights)
                {
                    sf::CircleShape mark(CELL / 6);
                    mark.setFillColor(sf::Color::Green);
                    mark.setPosition(
                        h.y * CELL + CELL / 2 - CELL / 12,
                        h.x * CELL + CELL / 2 - CELL / 12
                    );
                    window.draw(mark);
                }

                if (board[i][j] != EMPTY)
                {
                    sf::CircleShape piece(CELL / 2 - 10);
                    piece.setPosition(j * CELL + 10, i * CELL + 10);

                    if (board[i][j] == RED)
                        piece.setFillColor(sf::Color::Red);
                    else if (board[i][j] == BLUE)
                        piece.setFillColor(sf::Color::Blue);
                    else if (board[i][j] == RED_TRACE)
                        piece.setFillColor(sf::Color(255, 150, 150));
                    else if (board[i][j] == BLUE_TRACE)
                        piece.setFillColor(sf::Color(150, 150, 255));

                    window.draw(piece);
                    //画选中边框
                    if (pieceSelected && ((redTurn && board[i][j] == RED) || (!redTurn && board[i][j] == BLUE)))
                    {
                        sf::CircleShape outline(CELL / 2 - 4);
                        outline.setPosition(j * CELL + 4, i * CELL + 4);
                        outline.setFillColor(sf::Color::Transparent);
                        outline.setOutlineThickness(4);
                        outline.setOutlineColor(sf::Color::White);



                        window.draw(outline);
                    }
                }


            }
        }
    }

    window.display();

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            int x = event.mouseButton.y / CELL;
            int y = event.mouseButton.x / CELL;
            handleClick(x, y);
        }
    }


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
                int x = event.mouseButton.y / CELL;
                int y = event.mouseButton.x / CELL;
                handleClick(x, y);
            }
        }

        if (!gameOver)
            update();

        render();
    }
}