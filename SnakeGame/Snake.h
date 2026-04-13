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
        DirectionTurn direction;
    };

    struct SnakeSegment
    {
        Direction direction;
        /* Todo: отказаться от coord */
        sf::Vector2u coord;
        sf::Sprite sprite;
        std::queue<TurnPoint> turnPoints;
    };

    struct Snake
    {
        std::vector<SnakeSegment> segments;
        sf::Texture headTexture, bodyTexture, bodyAngleTexture, tailTexture;
        std::vector<sf::RectangleShape> turnPointShapes;
        float speed = 100.f;
        // float segmentSize; /* ? */
    };

    TurnPoint CreateTurnPoint(const SnakeSegment& segment, const Direction& from, const Direction& to);
    void UpdateTurnPoint(SnakeSegment& segment, const sf::Vector2f& position, const float& computedDistance);
    
    sf::RectangleShape CreateTurnPointShape(const sf::Vector2f& position, const sf::Vector2f& origin);
    void UpdateTurnPointShape(std::vector<sf::RectangleShape>& shapes, const sf::Vector2f& position);
    void DrawTurnPointShape(sf::RenderWindow& window, const Snake& snake);

    SnakeSegment CreateSnakeSegment(const sf::Vector2u& coord, const sf::Texture& texture);
    bool HasHeadSegmentOppositeDirection(const SnakeSegment& segment, Direction direction);
    void TryChangeHeadSegmentDirection(Snake& snake, Direction newDirection);
    void MoveSnakeSegment(SnakeSegment& segment, sf::Vector2f& position, const float& distance);
    void SetSnakeSegmentCenterPosition(SnakeSegment& segment);
    void UpdateSnakeSegmentCoord(SnakeSegment& segment, const sf::Vector2f& position);
    void UpdateSnakeSegmentRotation(SnakeSegment& segment);

    void SnakeKeyboardHandler(Snake& snake);

    void InitSnake(Snake& snake);
    void UpdateSnakeMovement(Snake& snake, const float& deltaTime);
    void DrawSnake(sf::RenderWindow& window, const Snake& snake);
}
