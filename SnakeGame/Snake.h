#pragma once
#include <queue>

#include "SFML/Graphics.hpp"
#include "Shared/Direction.h"
#include "Field.h"

namespace SnakeGame
{
    struct TurnPoint
    {
        sf::Vector2f position;
        Direction direction;
    };

    struct SnakeSegment
    {
        Direction direction;
        sf::Vector2u coord;
        sf::Sprite sprite;
        std::queue<TurnPoint> turnPoints;
    };

    struct Snake
    {
        std::vector<SnakeSegment> segments;
        sf::Texture headTexture, bodyTexture, bodyAngleTexture, tailTexture;
        float speed = 100.f;
        // float segmentSize; /* ? */
    };

    SnakeSegment CreateSnakeSegment(const sf::Vector2u& coord, const sf::Texture& texture);
    bool HasHeadSegmentOppositeDirection(const SnakeSegment& segment, Direction direction);
    void TryChangeHeadSegmentDirection(Snake& snake, Direction newDirection);
    void MoveSnakeSegment(SnakeSegment& segment, sf::Vector2f& position, float speed, const float& deltaTime);
    void SetSnakeSegmentCenterPosition(SnakeSegment& segment);
    void AddTurnPointsIntoSnakeSegments(Snake& snake, TurnPoint turnPoint);
    void UpdateSnakeSegmentCoord(SnakeSegment& segment, const sf::Vector2f& position);
    void UpdateSnakeSegmentRotation(SnakeSegment& segment);
    void SnakeKeyboardHandler(Snake& snake);

    void InitSnake(Snake& snake);
    void UpdateSnakeMovement(Snake& snake, const float& deltaTime);
    void DrawSnake(sf::RenderWindow& window, const Snake& snake);
}
