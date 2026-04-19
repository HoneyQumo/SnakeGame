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
        
        sf::Vector2f pos = oldTail.sprite.getPosition();
        switch (oldTail.direction)
        {
        case Direction::Up:    pos.y += CELL_HEIGHT; break;
        case Direction::Down:  pos.y -= CELL_HEIGHT; break;
        case Direction::Right: pos.x -= CELL_WIDTH;  break;
        case Direction::Left:  pos.x += CELL_WIDTH;  break;
        }
        newTail.sprite.setPosition(pos);

        oldTail.type = SegmentType::Body;
        oldTail.sprite.setTexture(assets.snakeBody);
        SetSpriteSize(oldTail.sprite, CELL_WIDTH, CELL_HEIGHT);
        SetSpriteOrigin(oldTail.sprite, 0.5f, 0.5f);
        UpdateSegmentRotation(oldTail);

        snake.segments.push_back(std::move(newTail));
    }
    
    // void GrowSnake(Snake& snake, const Assets& assets)
    // {
    //     if (snake.segments.empty()) return;
    //
    //     Segment& oldTail = snake.segments.back();
    //
    //     Segment newTail = oldTail;               // копируем position/direction/turnPoints/transform
    //     newTail.type = SegmentType::Tail;
    //     newTail.sprite.setTexture(assets.snakeTail);
    //     SetSpriteSize(newTail.sprite, CELL_WIDTH, CELL_HEIGHT);
    //     SetSpriteOrigin(newTail.sprite, 0.5f, 0.5f);
    //     UpdateSegmentRotation(newTail);
    //
    //     // Новый сегмент должен быть "позади" хвоста на 1 клетку, иначе он будет ехать поверх него.
    //     sf::Vector2f pos = oldTail.sprite.getPosition();
    //     switch (oldTail.direction)
    //     {
    //     case Direction::Up:    pos.y += CELL_HEIGHT; break;
    //     case Direction::Down:  pos.y -= CELL_HEIGHT; break;
    //     case Direction::Right: pos.x -= CELL_WIDTH;  break;
    //     case Direction::Left:  pos.x += CELL_WIDTH;  break;
    //     }
    //     newTail.sprite.setPosition(pos);
    //
    //     oldTail.type = SegmentType::Body;
    //     oldTail.sprite.setTexture(assets.snakeBody);
    //     SetSpriteSize(oldTail.sprite, CELL_WIDTH, CELL_HEIGHT);
    //     SetSpriteOrigin(oldTail.sprite, 0.5f, 0.5f);
    //     UpdateSegmentRotation(oldTail);
    //
    //     snake.segments.push_back(std::move(newTail));
    // }

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
