#pragma once
#include "SFML/Graphics.hpp"
#include "Segment.h"
#include "TurnPoint.h"
#include "../Shared/Assets.h"

namespace SnakeGame
{
    struct Snake
    {
        std::vector<Segment> segments;
        bool canChangeDirection = true;
        unsigned points = 0;
    };

    void InitSnake(Snake& snake, const Assets& assets);
    void GrowSnake(Snake& snake, const Assets& assets);
    void SnakeControl(Snake& snake);
    void UpdateSnake(Snake& snake, float computedDistance);
    void DrawSnake(sf::RenderWindow& window, const Snake& snake);

    struct Field;
    bool HasSnakeCollisionWithWall(const Segment& head, const Field& field);
    bool HasSnakeCollisionWithSelf(const Snake& snake);
}
