#include "Field.h"
#include "Game.h"

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

    std::vector<sf::Vector2u> GetAvailableCoords(const Game& game)
    {
        std::vector<sf::Vector2u> availableCells;
        availableCells.reserve(NUMBER_CELLS * NUMBER_CELLS);

        for (unsigned x = 0; x < NUMBER_CELLS; ++x)
        {
            for (unsigned y = 0; y < NUMBER_CELLS; ++y)
            {
                const sf::Vector2u currentCoord(x, y);

                const auto& cell = game.field.cells[x][y];
                if (cell.type == CellType::Wall) continue;

                bool isSnake = false;
                for (auto& segment : game.snake.segments)
                {
                    const auto& segmentPosition = GetCoordFromPosition(segment.sprite.getPosition());
                    if (segmentPosition.x == currentCoord.x && segmentPosition.y == currentCoord.y)
                    {
                        isSnake = true;
                        break;
                    }
                }

                if (!isSnake)
                {
                    availableCells.push_back(currentCoord);
                }
            }
        }

        return availableCells;
    }
}
