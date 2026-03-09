#pragma once
#include <SFML/Graphics.hpp>
#include"Board.h"
#include"Renderer.h"
#include"Player.h"
#include"Types.h"
#include"Heart.h"
#include"RenderState.h"

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
    //角色

    Player redPlayer{ RED_SIDE };
    Player bluePlayer{ BLUE_SIDE };

    Player* currentPlayer;
    Player* opponentPlayer;

    //流程
    void switchTurn();
    //bool redTurn;
    void update();
    void render();
    RenderState buildRenderState() const;
    Renderer renderer;
    //跳跃
    bool jumpMode;
    void performJump(PlayerSide side, int x2, int y2);
    //流程结束
    bool gameOver;
    PlayerSide winner;
    PlayerSide lastWinner;
    //点击
    void handleClick(int x, int y);
    void handleHeartClick(int x, int y);

    bool selected;
    std::vector<sf::Vector2i> highlights;
    void updateHighlights();

};