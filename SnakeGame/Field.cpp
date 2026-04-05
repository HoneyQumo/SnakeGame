#include "Field.h"

namespace SnakeGame
{
    void InitField(Field& field)
    {
        field.gridTexture.clear();
        field.gridTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);

        for (unsigned x = 0; x < NUMBER_CELLS; ++x)
        {
            for (unsigned y = 0; y < NUMBER_CELLS; ++y)
            {
                Cell& cell = field.cells[x][y];
                InitCell(cell, x, y);
                field.gridTexture.draw(cell.shape);
            }
        }
        field.gridTexture.display();
        field.gridSprite.setTexture(field.gridTexture.getTexture());
    }

    void DrawField(sf::RenderWindow& window, const Field& field)
    {
        window.draw(field.gridSprite);
    }
}
