#include "Heart.h"

//void ToughHeart::render(sf::RenderWindow& window, float x, float y) const
//{
//    sf::RectangleShape rect({ 20, 20 });
//    rect.setPosition(x, y);
//
//    if (consumed) {
//        rect.setFillColor(sf::Color(100, 100, 100)); // 已消耗-灰色
//    }
//    else if (active) {
//        rect.setFillColor(sf::Color(70, 130, 180)); // 激活-蓝色
//    }
//    else {
//        rect.setFillColor(sf::Color(100, 100, 150)); // 未激活-紫色
//    }
//
//    rect.setOutlineThickness(2);
//    rect.setOutlineColor(sf::Color::White);
//    window.draw(rect);
//}
//
//void DashHeart::render(sf::RenderWindow& window, float x, float y) const
//{
//    sf::CircleShape shape(12.f);
//    shape.setPosition(x, y);
//
//    if (consumed) {
//        shape.setFillColor(sf::Color(100, 100, 100)); // 已消耗-灰色
//    }
//    else if (active) {
//        shape.setFillColor(sf::Color(200, 200, 10)); // 激活-黄色
//    }
//    else {
//        shape.setFillColor(sf::Color(100, 100, 150)); // 未激活-紫色
//    }
//
//    shape.setOutlineThickness(2);
//    shape.setOutlineColor(sf::Color::White);
//    window.draw(shape);
//}

void ToughHeart::modifyMoves(const Board& board, PlayerSide side, std::vector<sf::Vector2i>& moves)
{


}

void DashHeart::modifyMoves(const Board& board, PlayerSide side, std::vector<sf::Vector2i>& moves)
{

}
