#pragma once
#include "SFML/Graphics.hpp"
#include "Shared/Direction.h"
#include "Field.h"

namespace SnakeGame
{
    struct SnakeSegment
    {
        Direction direction;
        sf::Vector2u coord;
        sf::Sprite sprite;
    };

    struct Snake
    {
        std::vector<SnakeSegment> segments;
        sf::Texture headTexture, bodyTexture, bodyEdgeTexture, tailTexture;
        float speed = 100.f;
        // float segmentSize; /* ? */
        // Direction direction = Direction::Right;
    };

    SnakeSegment CreateSnakeSegment(const sf::Vector2u& coord, const sf::Texture& texture);
    // void UpdateSnakeSegmentsCorner(Snake& snake);
    // void UpdateSnakeSegmentsPosition(Snake& snake, const Field& field, const float& percent);
    // void UpdateSnakeSegmentsCoord(Snake& snake);
    void UpdateSnakeSegmentRotation(SnakeSegment& segment);

    void SnakeKeyboardHandler(SnakeSegment& headSegment);

    void InitSnake(Snake& snake);
    void UpdateSnakeMovement(Snake& snake, const float& deltaTime);
    void DrawSnake(sf::RenderWindow& window, const Snake& snake);
}
