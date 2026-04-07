#pragma once
#include "Shared/Constants.h"
#include "Field.h"
#include "Snake.h"

namespace SnakeGame
{
    struct Game
    {
        Field field;
        Snake snake;
    };

    void InitGame(Game& game);
    void UpdateGame(Game& game, const float& deltaTime);
    void DrawGame(sf::RenderWindow& window, Game& game);
}
