#include "Heart.h"

void ToughHeart::render(sf::RenderWindow& window, float x, float y) const
{
    sf::CircleShape shape(12.f);
    shape.setPosition(x, y);

    if (consumed) {
        shape.setFillColor(sf::Color(100, 100, 100)); // 已消耗-灰色
    }
    else if (active) {
        shape.setFillColor(sf::Color(70, 130, 180)); // 激活-蓝色
    }
    else {
        shape.setFillColor(sf::Color(100, 100, 150)); // 未激活-紫色
    }

    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::White);
    window.draw(shape);
}
