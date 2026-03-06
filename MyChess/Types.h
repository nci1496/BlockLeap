#pragma once

#include<vector>

class IHeart;

enum PlayerSide
{
    RED_SIDE,
    BLUE_SIDE
};

inline PlayerSide getOpponent(PlayerSide side)
{
    return (side == RED_SIDE) ? BLUE_SIDE : RED_SIDE;
}

enum class HeartType {
    NORMAL,
    TOUGH_HEART,

};