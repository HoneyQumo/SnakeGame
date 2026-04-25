#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

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

        sf::SoundBuffer musicBuffer,
                        deathBuffer,
                        eatBuffer,
                        menuToggleBuffer,
                        menuSelectBuffer;

        sf::Sound music,
                  death,
                  eat,
                  menuToggle,
                  menuSelect;
    };
}
