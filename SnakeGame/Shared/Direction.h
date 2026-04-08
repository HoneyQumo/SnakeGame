#pragma once

namespace SnakeGame
{
    enum class Direction
    {
        Right = 0,
        Up = 1,
        Left = 2,
        Down = 3
    };

    enum class DirectionVertical
    {
        Up = static_cast<int>(Direction::Up),
        Down = static_cast<int>(Direction::Down)
    };

    enum class DirectionHorizontal
    {
        Left = static_cast<int>(Direction::Left),
        Right = static_cast<int>(Direction::Right)
    };

    struct DirectionTurn
    {
        Direction from;
        Direction to;
    };
}
