#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "../Shared/Direction.h"
#include "../Shared/Math.h"

namespace SnakeGame
{
    struct TurnPoint
    {
        sf::Vector2f position;
        Direction direction;
    };

    TurnPoint CreateTurnPoint(const sf::Vector2f& position, const Direction& direction);
}
