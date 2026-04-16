#pragma once
#include "SFML/Graphics.hpp"
#include "Segment.h"
#include "TurnPoint.h"

namespace SnakeGame
{
    struct Snake
    {
        std::vector<Segment> segments;
        sf::Texture headTexture, bodyTexture, bodyAngleTexture, tailTexture;
        std::vector<sf::Sprite> turnPointSprite;
        bool canChangeDirection = true;
        unsigned points = 0;
    };

    void InitSnake(Snake& snake);

    void SnakeControl(Snake& snake);

    void UpdateSnake(Snake& snake, float computedDistance);

    void DrawSnake(sf::RenderWindow& window, const Snake& snake);
}
