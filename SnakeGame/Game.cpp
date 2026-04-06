#include <cassert>
#include "Game.h"

namespace SnakeGame
{
    void InitGame(Game& game)
    {
        assert(game.snake.headTexture.loadFromFile(RESOURCES_GRAPHICS + "\\head_right.png"));
        assert(game.snake.bodyTexture.loadFromFile(RESOURCES_GRAPHICS + "\\body_horizontal.png"));
        assert(game.snake.tailTexture.loadFromFile(RESOURCES_GRAPHICS + "\\tail_left.png"));

        InitField(game.field);
        InitSnake(game.snake);
    }


    void UpdateGame(Game& game, float& movementTimer)
    {
        SnakeKeyboardHandler(game.snake.direction);
        UpdateSnakeMovement(game.snake, game.field, movementTimer);
    }

    void DrawGame(sf::RenderWindow& window, Game& game)
    {
        DrawField(window, game.field);
        DrawSnake(window, game.snake);
    }
}
