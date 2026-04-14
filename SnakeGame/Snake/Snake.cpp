#include "Snake.h"

namespace SnakeGame
{
    void InitSnake(Snake& snake)
    {
        snake.segments = {
            CreateSegment(SegmentType::Head, {7, 10}, snake.headTexture),
            CreateSegment(SegmentType::Body, {6, 10}, snake.bodyTexture),
            CreateSegment(SegmentType::Body, {5, 10}, snake.bodyTexture),
            CreateSegment(SegmentType::Body, {4, 10}, snake.bodyTexture),
            CreateSegment(SegmentType::Body, {3, 10}, snake.bodyTexture),
            CreateSegment(SegmentType::Body, {2, 10}, snake.bodyTexture),
            CreateSegment(SegmentType::Tail, {1, 10}, snake.tailTexture)
        };
    }

    void SnakeControl(Snake& snake)
    {
        if (!snake.canChangeDirection) return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            TryChangeHeadSegmentDirection(snake, Direction::Up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            TryChangeHeadSegmentDirection(snake, Direction::Down);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            TryChangeHeadSegmentDirection(snake, Direction::Right);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            TryChangeHeadSegmentDirection(snake, Direction::Left);
        }
    }

    void UpdateSnake(Snake& snake, const float& deltaTime)
    {
        const float computedDistance = snake.speed * deltaTime;

        for (unsigned i = 0; i < snake.segments.size(); ++i)
        {
            Segment& segment = snake.segments[i];

            if (segment.type == SegmentType::Head)
            {
                const auto oldPosition = GetCoordFromPosition(segment.sprite.getPosition());
                MoveSegment(segment, computedDistance);
                const auto newPosition = GetCoordFromPosition(segment.sprite.getPosition());

                if (oldPosition != newPosition)
                {
                    snake.canChangeDirection = true;
                }
            }
            else
            {
                MoveSegmentWithTurnPoints(segment, computedDistance);
            }

            if (!snake.turnPointSprite.empty() && segment.type == SegmentType::Tail)
            {
                const auto& position = segment.sprite.getPosition();
                UpdateTurnPointSprite(snake.turnPointSprite, position);
            }
        }
    }

    void DrawSnake(sf::RenderWindow& window, const Snake& snake)
    {
        for (auto& segment : snake.segments)
        {
            window.draw(segment.sprite);
        }
    }
}
