#pragma once
#include <SFML/Graphics.hpp>
#include<vector>
#include"Board.h"

class Renderer
{


public:
    static void draw(sf::RenderWindow& window,
        const Board& board,
        bool redTurn,
        bool gameOver,
        Piece winner,
        const std::vector<sf::Vector2i>& highlights,
        const bool& selected,
        const sf::Font& font);

};

