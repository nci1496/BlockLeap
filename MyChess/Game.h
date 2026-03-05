#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include"Board.h"
#include"Renderer.h"

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
    Board board;

private:
    sf::Font font;

private:

    sf::RenderWindow window;
    //角色状态
    int redHP;
    int blueHP;
    //流程
    bool redTurn;
    void update();
    void render();
    Renderer renderer;
    //跳跃
    bool jumpMode;
    void performJump(sf::Vector2i& pos, int x2, int y2);
    //流程结束
    bool gameOver;
    Piece winner;
    Piece lastWinner;
    //点击
    void handleClick(int x, int y);
    bool selected;
    std::vector<sf::Vector2i> highlights;
    void updateHighlights();
};