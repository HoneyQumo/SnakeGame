#pragma once
#include "Shared/Constants.h"
#include "Cell.h"

namespace SnakeGame
{
    struct Field
    {
        Cell cells[NUMBER_CELLS][NUMBER_CELLS] = {};

        sf::RenderTexture gridTexture;
    };

    void InitField(Field& field);

    void DrawField(sf::RenderWindow& window, const Field& field);

    struct Game;
    std::vector<sf::Vector2u> GetAvailableCoords(const Game& game);
}
