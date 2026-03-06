#pragma once
#include <SFML/Graphics.hpp>
#include "Types.h"
#include"Board.h"

struct RenderHeart {
    HeartType type;
    bool active;
    bool consumed;
    sf::Vector2i pos;

};

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
    std::vector<RenderHeart> redHearts;
    std::vector<RenderHeart> blueHearts;

    const sf::Font* font;
};