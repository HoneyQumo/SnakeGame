#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
    struct Assets
    {
        sf::Texture apple,
                    snakeHead,
                    snakeBody,
                    snakeBodyAngle,
                    snakeTail;

        sf::Font font;
    };
}
