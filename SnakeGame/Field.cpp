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
                cell.shape.setSize({CELL_WIDTH, CELL_HEIGHT});
                cell.shape.setPosition(static_cast<float>(x * CELL_WIDTH), static_cast<float>(y * CELL_HEIGHT));
                cell.shape.setFillColor((x + y) % 2 == 0 ? LIGHT_GREEN_COLOR : DARK_GREEN_COLOR);
            }
        }
    }
}
