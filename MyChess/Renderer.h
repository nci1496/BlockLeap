#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include"Board.h"
#include"Types.h"

struct RenderState
{
    const Board* board;

    bool redTurn;
    bool gameOver;
    PlayerSide winner;

    bool selected;
    const std::vector<sf::Vector2i>* highlights;

    int redHP;
    int blueHP;

    const sf::Font* font;
};



class Renderer
{


public:
    static void draw(sf::RenderWindow& window,const RenderState&state);


};

