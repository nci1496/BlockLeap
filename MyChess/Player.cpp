#include "Player.h"

Player::Player(PlayerSide s)
    : side(s), hp(5)
{

}

void Player::damage(int amount)
{
    hp -= amount;
    if (hp < 0)
    {
        hp = 0;
    }
}

void Player::heal(int amount)
{
    hp += amount;
    if (hp > maxHP) { hp = maxHP; }
}

int Player::getHP() const
{
    return hp;
}

PlayerSide Player::getSide() const
{
    return side;
}

bool Player::isDead() const
{
    return hp <= 0;
}

JumpCount Player::getJumpCount()
{
    return jumpCount;
}

void Player::setJumpCount(int selfCount, int totalCount)
{
    jumpCount.eatenSelf = selfCount;
    jumpCount.eatenTotal = totalCount;

}

void Player::applyJumpResult()
{
    damage(jumpCount.eatenSelf);
    switch (jumpCount.eatenTotal)
    {
        case 1:
        {damage(1);break;}
        case 2:
        {heal(1);break;}
        case 3:
        {heal(3);break;}
        
    }
    if (jumpCount.eatenTotal >= 4)
    {
        heal(maxHP);
    }

    setJumpCount(0,0);
}

