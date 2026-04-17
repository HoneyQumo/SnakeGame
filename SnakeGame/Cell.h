#pragma once
#include "SFML/Graphics.hpp"
#include "Shared/Constants.h"

namespace SnakeGame
{
    enum class CellType
    {
        Default = 0,
        Wall,
    };

    struct Cell
    {
        CellType type = CellType::Default;
        sf::RectangleShape shape;
    };

    void InitCell(Cell& cell, sf::Vector2u position, const CellType& type = CellType::Default);
}
