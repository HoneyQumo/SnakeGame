#include "Snake.h"
#include "../Field.h"

namespace SnakeGame
{
    void InitSnake(Snake& snake, const Assets& assets)
    {
        snake.points = 0;
        snake.canChangeDirection = true;
        snake.segments = {
            CreateSegment(SegmentType::Head, {4, NUMBER_CELLS / 2}, assets.snakeHead),
            CreateSegment(SegmentType::Body, {3, NUMBER_CELLS / 2}, assets.snakeBody),
            CreateSegment(SegmentType::Body, {2, NUMBER_CELLS / 2}, assets.snakeBody),
            CreateSegment(SegmentType::Tail, {1, NUMBER_CELLS / 2}, assets.snakeTail)
        };
    }

    void GrowSnake(Snake& snake, const Assets& assets)
    {
        if (snake.segments.empty()) return;

        Segment& oldTail = snake.segments.back();
        Segment newTail = oldTail;

        sf::Vector2f position = oldTail.sprite.getPosition();
        switch (oldTail.direction)
        {
        case Direction::Up:
            position.y += CELL_HEIGHT;
            break;
        case Direction::Down:
            position.y -= CELL_HEIGHT;
            break;
        case Direction::Right:
            position.x -= CELL_WIDTH;
            break;
        case Direction::Left:
            position.x += CELL_WIDTH;
            break;
        }
        newTail.sprite.setPosition(position);

        oldTail.type = SegmentType::Body;
        oldTail.sprite.setTexture(assets.snakeBody);
        SetSpriteSize(oldTail.sprite, CELL_WIDTH, CELL_HEIGHT);
        SetSpriteOrigin(oldTail.sprite, 0.5f, 0.5f);
        UpdateSegmentRotation(oldTail);

        snake.segments.push_back(std::move(newTail));
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
        /* Collision with window border */
        const auto position = head.sprite.getPosition();
        const auto nearestCenter = GetNearestCenter(position);
        const auto coord = GetCoordFromPosition(nearestCenter);

        if (coord.x < 0 || coord.y < 0 || coord.x >= static_cast<int>(NUMBER_CELLS) || coord.y >= static_cast<int>(NUMBER_CELLS))
        {
            return true;
        }

        /* Collision with wall */
        if (field.cells[coord.x][coord.y].type == CellType::Wall)
        {
            return true;
        }
        
        return false;
    }

    bool HasSnakeCollisionWithSelf(const Snake& snake)
    {
        if (snake.segments.size() < 4) return false;

        const auto headCoord = GetCoordFromPosition(GetNearestCenter(snake.segments[0].sprite.getPosition()));

        for (unsigned i = 2; i < snake.segments.size(); ++i)
        {
            const auto segmentCoord = GetCoordFromPosition(GetNearestCenter(snake.segments[i].sprite.getPosition()));
            if (segmentCoord == headCoord)
            {
                return true;
            }
        }

        return false;
    }
}
