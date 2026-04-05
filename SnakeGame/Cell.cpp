#include "Cell.h"

namespace SnakeGame
{
    void InitCell(Cell& cell, const unsigned& x, const unsigned& y)
    {
        cell.shape.setSize({CELL_WIDTH, CELL_HEIGHT});
        cell.shape.setPosition(static_cast<float>(x * CELL_WIDTH), static_cast<float>(y * CELL_HEIGHT));
        cell.shape.setFillColor((x + y) % 2 == 0 ? LIGHT_GREEN_COLOR : DARK_GREEN_COLOR);
    }
}
