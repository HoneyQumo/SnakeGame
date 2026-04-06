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
        sf::Vector2f position;
        sf::Sprite sprite;
    };

    struct Snake
    {
        std::vector<SnakeSegment> segments;
        sf::Texture headTexture, bodyTexture, tailTexture;
        // float segmentSize; /* ? */
        float speed = 5.f;
        Direction direction = Direction::Right;
    };

    SnakeSegment CreateSnakeSegment(const sf::Vector2u& coord, const sf::Texture& texture);
    void UpdateSnakeSegmentsPosition(Snake& snake, const Field& field, const float& percent);
    void UpdateSnakeSegmentsCoord(Snake& snake);
    void DrawSnakeSegment(sf::RenderWindow& window, SnakeSegment& segment);

    void SnakeKeyboardHandler(Direction& direction);

    void InitSnake(Snake& snake);
    void UpdateSnakeMovement(Snake& snake, const Field& field, float& movementTimer);
    void DrawSnake(sf::RenderWindow& window, Snake& snake);
}
