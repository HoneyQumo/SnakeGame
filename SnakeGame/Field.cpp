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
                const bool IS_PERIMETER = x == 0 || x == NUMBER_CELLS - 1 || y == 0 || y == NUMBER_CELLS - 1 || (x == 5 && y == 5);
                InitCell(cell, {x, y}, IS_PERIMETER ? CellType::Wall : CellType::Default);
                field.gridTexture.draw(cell.shape);
            }
        }
        
        // field.gridSprite.setTexture(field.gridTexture.getTexture(), true);
    }

    void DrawField(sf::RenderWindow& window, const Field& field)
    {
        for (auto& row : field.cells)
        {
            for (auto& cell : row)
            {
                window.draw(cell.shape);    
            }
            
        }

        // window.draw(field.gridSprite);
    }
}
