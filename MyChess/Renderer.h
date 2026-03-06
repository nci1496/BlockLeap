#pragma once
#include <SFML/Graphics.hpp>
#include"Board.h"
#include"Types.h"
#include"RenderState.h"





class Renderer
{

public:
    static void draw(sf::RenderWindow& window,const RenderState&state);
private:
    static void drawHearts(sf::RenderWindow& window,const std::vector<RenderHeart>& hearts);
};

