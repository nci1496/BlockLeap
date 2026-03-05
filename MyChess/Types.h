#pragma once
enum PlayerSide
{
    RED_SIDE,
    BLUE_SIDE
};

inline PlayerSide getOpponent(PlayerSide side)
{
    return (side == RED_SIDE) ? BLUE_SIDE : RED_SIDE;
}