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
        /* Todo: отказаться от coord */
        sf::Vector2u coord;
        sf::Sprite sprite;
        std::queue<TurnPoint> turnPoints;
    };

    struct Snake
    {
        std::vector<SnakeSegment> segments;
        sf::Texture headTexture, bodyTexture, bodyAngleTexture, tailTexture;
        std::vector<sf::Sprite> turnPointShapes;
        float speed = 100.f;
        // float segmentSize; /* ? */
    };

    TurnPoint CreateTurnPoint(const SnakeSegment& segment, const Direction& direction);
    void UpdateTurnPoint(SnakeSegment& segment, const sf::Vector2f& position, const float& computedDistance);

    sf::Sprite CreateTurnPointSprite(const sf::Texture& texture, const sf::Vector2f& position, const DirectionTurn& directionTurn);
    void UpdateTurnPointSprite(std::vector<sf::Sprite>& shapes, const sf::Vector2f& position);
    void SetTurnPointSpriteRotation(sf::Sprite& sprite, const DirectionTurn& directionTurn);
    void DrawTurnPointSprite(sf::RenderWindow& window, const Snake& snake);

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
