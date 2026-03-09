#pragma once
#include <SFML/Graphics.hpp>
#include"Types.h"

#include"Board.h"

class IHeart {
public:
    virtual ~IHeart() = default;
    virtual void onActivate() = 0;        // 玩家点击激活
    virtual void switchActivate()=0;

    virtual bool onDamage(int& damage) = 0; // 扣血时处理，返回是否消耗心抵挡伤害
    //virtual void render(sf::RenderWindow& window, float x, float y) const = 0; // 绘制,不需要，因为Render里面画了
    virtual bool isActive() const = 0;   // 是否激活
    virtual bool isConsumed() const = 0;    // 是否消耗完
    virtual HeartType getType() const = 0;

    virtual void modifyMoves(const Board& board, PlayerSide side,
        std::vector<sf::Vector2i>& moves) {};//调整和Heart相关的移动 默认不处理
};

class NormalHeart : public IHeart {
    bool active = true;
    bool consumed = false;
public:
    void onActivate() override {
        if (!consumed) active = true;  // 激活护盾
    }
    void switchActivate() override { active = active; }//默认不能修改 
    bool onDamage(int& damage) override { return false; } // 普通心无防御
    //void render(sf::RenderWindow& window, float x, float y) const override {
    //    sf::RectangleShape rect({ 20.f,20.f });
    //    rect.setFillColor(active ? sf::Color(200, 200, 200) : sf::Color(150, 150, 150));
    //    rect.setPosition(x, y);
    //    window.draw(rect);
    //}
    bool isActive() const override { return active; }
    bool isConsumed() const override { return false; }
    HeartType getType() const override { return HeartType::NORMAL; }
};

class ToughHeart : public IHeart {
    bool active = true;
    bool consumed = false;
public:
    void onActivate() override {
        if (!consumed) active = true;  // 激活护盾
    }

    void switchActivate() override { active = !active; }

    bool onDamage(int &damage) override {
        if (active && !consumed) {
            consumed = true;  // 一次性使用
            active = false;
            return true;       // 吸收所有伤害
        }
        return false;
    }

    //void render(sf::RenderWindow& window, float x, float y) const override;

    bool isActive() const override { return active && !consumed; }
    bool isConsumed() const override { return consumed; }
    HeartType getType() const override { return HeartType::TOUGH_HEART; }

    void modifyMoves(const Board& board, PlayerSide side,
        std::vector<sf::Vector2i>& moves) override;//调整和Heart相关的移动

};

class DashHeart : public IHeart {
    bool active = true;
    bool consumed = false;
public:
    void onActivate() override {
        if (!consumed) active = true; 
    }

    void switchActivate() override { active = !active; }

    bool onDamage(int& damage) override { return false; }//不提供伤害相关的效果

    //void render(sf::RenderWindow& window, float x, float y) const override;

    bool isActive() const override { return active && !consumed; }
    bool isConsumed() const override { return consumed; }
    HeartType getType() const override { return HeartType::DASH_HEART; }

    void modifyMoves(const Board& board, PlayerSide side,
        std::vector<sf::Vector2i>& moves) override;//调整和Heart相关的移动

};