#include "Game.h"

namespace SnakeGame
{
    void DrawGame(sf::RenderWindow& window, Game& game)
    {
        DrawField(window, game.field);
    }
}
