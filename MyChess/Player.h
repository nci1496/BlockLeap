#pragma once
#include"Types.h"

class Player
{
public:
    Player(PlayerSide side);

    void damage(int amount);
    void heal(int amount);

    int getHP() const;
    PlayerSide getSide() const;
    bool isDead() const;

private:
    PlayerSide side;
    int hp;
};