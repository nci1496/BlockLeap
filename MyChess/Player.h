#pragma once
#include"Types.h"

struct 
JumpCount
{
    int eatenSelf=0;
    int eatenTotal=0;
};

class Player
{
public:
    Player(PlayerSide side);

    void damage(int amount);
    void heal(int amount);

    int getHP() const;
    PlayerSide getSide() const;
    bool isDead() const;

    //³Ô×ÓÏà¹Ø
    JumpCount jumpCount;
    JumpCount getJumpCount();
    void setJumpCount(int selfCount,int totalCount);
    void applyJumpResult();

private:
    PlayerSide side;
    int hp;
    const int maxHP = 5;
};