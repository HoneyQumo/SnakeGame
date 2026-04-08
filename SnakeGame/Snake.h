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
    };

    SnakeSegment CreateSnakeSegment(const sf::Vector2u& coord, const sf::Texture& texture);
    bool CheckHeadSegmentDirectionMovement(const SnakeSegment& segment, Direction direction);
    void TryChangeHeadSegmentDirection(SnakeSegment& headSegment, Direction newDirection);
    void MoveSnakeSegment(SnakeSegment& segment, float speed, const float& deltaTime);
    void SetSnakeSegmentCenterPosition(SnakeSegment& segment);
    void UpdateSnakeSegmentCoord(SnakeSegment& segment);
    void UpdateSnakeSegmentRotation(SnakeSegment& segment);

    void SnakeKeyboardHandler(SnakeSegment& headSegment);

    void InitSnake(Snake& snake);
    void UpdateSnakeMovement(Snake& snake, const float& deltaTime);
    void DrawSnake(sf::RenderWindow& window, const Snake& snake);
}
