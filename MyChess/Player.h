#pragma once
#include"Types.h"
#include"Heart.h"

struct JumpCount
{
    int eatenSelf=0;
    int eatenTotal=0;
};

class Player
{

private:
    int HP;
    int maxHP = 5;
    std::vector<std::unique_ptr<IHeart>> hearts;

public:
    Player(PlayerSide side);
    //血量
    void heal(int amount);
    int getHP() const;
    int getMaxHP()const;
    int getHeartCount()const;
    const IHeart* getHeart(int index)const;
    void addHeart(std::unique_ptr<IHeart> heart);

    void activateHeart(int index);
    void switchActivateHeart(int index);
    
public:

    PlayerSide getSide() const;
    bool isDead() const;

    //吃子相关
    JumpCount jumpCount;
    JumpCount getJumpCount();
    void setJumpCount(int selfCount,int totalCount);
    void applyJumpResult();
    void takeDamage(int dmg);
private:
    PlayerSide side;



};