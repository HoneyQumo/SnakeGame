#include "Cell.h"

namespace SnakeGame
{
    void InitCell(Cell& cell, const sf::Vector2u position, const CellType& type)
    {
        cell.type = type;
        cell.shape.setSize({CELL_WIDTH, CELL_HEIGHT});
        cell.shape.setPosition(static_cast<float>(position.x * CELL_WIDTH), static_cast<float>(position.y * CELL_HEIGHT));

        switch (cell.type)
        {
        case CellType::Default:
            cell.shape.setFillColor((position.x + position.y) % 2 == 0 ? LIGHT_GREEN_COLOR : DARK_GREEN_COLOR);
            break;
        case CellType::Wall:
            cell.shape.setFillColor(GRAY_COLOR);
            break;
        }
    }
}
