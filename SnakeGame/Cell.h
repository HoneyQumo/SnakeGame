#pragma once
#include "SFML/Graphics.hpp"
#include "Shared/Constants.h"

namespace SnakeGame
{
    struct Cell
    {
        sf::RectangleShape shape;
    };

    void InitCell(Cell& cell, const unsigned& x, const unsigned& y);
}
