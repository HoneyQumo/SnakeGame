#pragma once
#include "SFML/Graphics.hpp"
#include "Shared/Direction.h"
#include "Field.h"

namespace SnakeGame
{
    struct SnakeSegment
    {
        sf::Vector2u coord;
        sf::Vector2u oldCoord;
        sf::Sprite sprite;
        sf::Vector2i direction;
    };

    struct Snake
    {
        std::vector<SnakeSegment> segments;
        sf::Texture headTexture, bodyTexture, bodyEdgeTexture, tailTexture;
        float speed = 1.f;
        // float segmentSize; /* ? */
        // Direction direction = Direction::Right;
    };

    SnakeSegment CreateSnakeSegment(const sf::Vector2u& coord, const sf::Texture& texture);
    void UpdateSnakeSegmentsCorner(Snake& snake);
    void UpdateSnakeSegmentsPosition(Snake& snake, const Field& field, const float& percent);
    void UpdateSnakeSegmentsCoord(Snake& snake);
    void UpdateSnakeSegmentRotation(SnakeSegment& segment);

    void SnakeKeyboardHandler(SnakeSegment& headSegment);

    void InitSnake(Snake& snake);
    void UpdateSnakeMovement(Snake& snake, const Field& field, float& movementTimer);
    void DrawSnake(sf::RenderWindow& window, Snake& snake);
}
