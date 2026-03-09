#include "Player.h"
#include<iostream>

Player::Player(PlayerSide s)
    : side(s), HP(5)
{

}

void Player::heal(int amount)
{
    HP += amount;
    if (HP > maxHP) { HP = maxHP; }
}

int Player::getHP() const
{
    return HP;
}

int Player::getMaxHP() const
{
    return maxHP;
}

int Player::getHeartCount() const
{
    return hearts.size();
}

const IHeart* Player::getHeart(int index) const
{
    if (index < 0 || index >= hearts.size())
        return nullptr;

    return hearts[index].get();
}

void Player::addHeart(std::unique_ptr<IHeart> heart)
{
     hearts.push_back(std::move(heart)); 
}

void Player::activateHeart(int index)
{
    if (index >= 0 && index < hearts.size())
    {
        hearts[index]->onActivate();
    }
}

void Player::switchActivateHeart(int index)
{
    if (index >= 0 && index < hearts.size())
    {
        hearts[index]->switchActivate();
    }
}

bool Player::hasActiveHeart(HeartType type) const
{
    for (const auto& heart : hearts)
    {
        if (heart->getType() == type &&
            heart->isActive() &&
            !heart->isConsumed())
        {
            return true;
        }
    }
    return false;
}

IHeart* Player::getActiveHeart(HeartType type)
{
    for (auto& heart : hearts)
    {
        if (heart->getType() == type &&
            heart->isActive() &&
            !heart->isConsumed())
        {
            return heart.get();
        }
    }
    return nullptr;
}

PlayerSide Player::getSide() const
{
    return side;
}

bool Player::isDead() const
{
    return HP <= 0;
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
    takeDamage(jumpCount.eatenSelf);
    switch (jumpCount.eatenTotal)
    {
        case 1:
        {takeDamage(1);break;}
        case 2:
        {heal(1);
        //addHeart(std::make_unique<DashHeart>());//only test
        //std::cout << "add hearts";
        break;}
        case 3:
        {addHeart(std::make_unique<ToughHeart>()); break;}
        //case 4: {

        //    addHeart(std::make_unique<DashHeart>());
        //    break;
        //
        //}

        default:
        {
            if (jumpCount.eatenTotal >= 4)
            {
                heal(maxHP);

                addHeart(std::make_unique<ToughHeart>()); 
                //addHeart(std::make_unique<DashHeart>());
                break;

            }
        }
    }
    

    setJumpCount(0,0);
}

void Player::takeDamage(int damage) {
    if (damage <= 0) return;

    // 规则1: 优先消耗普通心(HP)
    if (damage == 1 && HP > 0) {
        // 小伤害优先用HP吸收
        HP--;
        return;
    }

    // 规则2: 大伤害或HP不足时
    if (damage > 1 || HP <= 0) {
        // 2.1 尝试用坚毅之心吸收

        if (hasActiveHeart(HeartType::TOUGH_HEART))
        {
            IHeart* heart = getActiveHeart(HeartType::TOUGH_HEART);
            
                if (heart->onDamage(damage))
                {
                    return;// 坚毅之心吸收成功
                }
        }

        // 2.2 没有坚毅之心可用，扣减HP
        HP -= damage;
        if (HP < 0)
        {
            HP = 0;
        };
    }
}
