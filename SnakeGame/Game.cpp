#include <cassert>
#include "Game.h"

namespace SnakeGame
{
    void InitGame(Game& game)
    {
        assert(game.snake.headTexture.loadFromFile(RESOURCES_GRAPHICS + "\\head_right.png"));
        assert(game.snake.bodyTexture.loadFromFile(RESOURCES_GRAPHICS + "\\body_horizontal.png"));
        assert(game.snake.bodyAngleTexture.loadFromFile(RESOURCES_GRAPHICS + "\\body_bottomright.png"));
        assert(game.snake.tailTexture.loadFromFile(RESOURCES_GRAPHICS + "\\tail_left.png"));

        InitField(game.field);
        InitSnake(game.snake);
    }


    void UpdateGame(Game& game, const float& deltaTime)
    {
        SnakeControl(game.snake);
        UpdateSnake(game.snake, deltaTime);
    }

    void DrawGame(sf::RenderWindow& window, const Game& game)
    {
        DrawField(window, game.field);
        DrawSnake(window, game.snake);
        DrawTurnPointSprite(window, game.snake);
    }
}
