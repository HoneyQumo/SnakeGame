#pragma once
#include "Constants.h"
#include "Field.h"

namespace SnakeGame
{
    struct Game
    {
        Field field;
    };

    void DrawGame(sf::RenderWindow& window, Game& game);
}
