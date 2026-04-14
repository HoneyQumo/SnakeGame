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
        float speed = 200.f;
        bool canChangeDirection = true;
    };


    void InitSnake(Snake& snake);

    void SnakeControl(Snake& snake);

    void UpdateSnake(Snake& snake, const float& deltaTime);

    void DrawSnake(sf::RenderWindow& window, const Snake& snake);
}
