#include "Snake.h"
#include "../Field.h"

namespace SnakeGame
{
    void InitSnake(Snake& snake, const Assets& assets)
    {
        snake.points = 0;
        snake.canChangeDirection = true;
        snake.segments = {
            CreateSegment(SegmentType::Head, {7, 10}, assets.snakeHead),
            CreateSegment(SegmentType::Body, {6, 10}, assets.snakeBody),
            CreateSegment(SegmentType::Body, {5, 10}, assets.snakeBody),
            CreateSegment(SegmentType::Body, {4, 10}, assets.snakeBody),
            CreateSegment(SegmentType::Body, {3, 10}, assets.snakeBody),
            CreateSegment(SegmentType::Body, {2, 10}, assets.snakeBody),
            CreateSegment(SegmentType::Tail, {1, 10}, assets.snakeTail)
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

    void UpdateSnake(Snake& snake, const float computedDistance)
    {
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

    bool HasSnakeCollisionWithWall(const Segment& head, const Field& field)
    {
        const auto coord = GetCoordFromPosition(head.sprite.getPosition());
        const auto cell = field.cells[coord.x][coord.y];

        return cell.type == CellType::Wall;
    }
}
