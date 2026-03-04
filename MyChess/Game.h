#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum Piece {
    EMPTY,
    RED,
    BLUE,
    RED_TRACE,
    BLUE_TRACE
};

enum GameState
{
    MENU,
    PLAYING,
    GAMEOVER
};

class Game {
public:
    Game();
    void run();

    GameState state;

//资源
private:
    sf::Font font;

private:
    static const int SIZE = 8;
    static const int CELL = 80;

    std::vector<std::vector<Piece>> board;

    sf::Vector2i redPos;
    sf::Vector2i bluePos;

    sf::RenderWindow window;
    void handleEvents();

    bool redTurn;
    bool selected;
    bool jumpMode;

    void handleClick(int x, int y);
    void update();
    void render();

    bool inside(int x, int y);
    bool isQueenMove(int x1, int y1, int x2, int y2);
    bool canJump(int x, int y, int x2, int y2);
    bool hasAnyJump(sf::Vector2i pos);

    //可跳点高亮
    std::vector<sf::Vector2i> highlights;
    void calculateHighlights();
    //选中高亮
    bool pieceSelected;

    void performJump(sf::Vector2i& pos, int x2, int y2);
    


    bool gameOver;
    Piece winner;


    int boardSize;        // 用户选择
    Piece lastWinner;     // 记录赢家

};