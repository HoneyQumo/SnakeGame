#pragma once
#include "Field.h"
#include "Shared/Constants.h"
#include "Snake/Snake.h"

namespace SnakeGame
{
    struct Game
    {
        Field field;
        Snake snake;
    };

    void InitGame(Game& game);
    void UpdateGame(Game& game, const float& deltaTime);
    void DrawGame(sf::RenderWindow& window, const Game& game);
}
