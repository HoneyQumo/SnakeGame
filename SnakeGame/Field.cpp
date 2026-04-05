#include "Field.h"

namespace SnakeGame
{
    void InitField(Field& field)
    {
        for (unsigned x = 0; x < NUMBER_CELLS; ++x)
        {
            for (unsigned y = 0; y < NUMBER_CELLS; ++y)
            {
                Cell& cell = field.cells[x][y];
                InitCell(cell, x, y);
            }
        }
    }

    void DrawField(sf::RenderWindow& window, Field& field)
    {
        for (auto& row : field.cells)
        {
            for (auto& cell : row)
            {
                window.draw(cell.shape);
            }
        }
    }
}
