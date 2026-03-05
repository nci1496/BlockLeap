#include "Player.h"

Player::Player(PlayerSide s)
    : side(s), hp(5)
{
}

void Player::damage(int amount)
{
    hp -= amount;
    if (hp < 0)
        hp = 0;
}

void Player::heal(int amount)
{
    hp += amount;
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