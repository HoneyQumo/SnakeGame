#pragma once
#include "Constants.h"
#include "Cell.h"

namespace SnakeGame
{
    struct Field
    {
        Cell cells[NUMBER_CELLS][NUMBER_CELLS] = {};

        sf::RenderTexture gridTexture;
        sf::Sprite gridSprite;
    };

    void InitField(Field& field);

    void DrawField(sf::RenderWindow& window, const Field& field);
}
