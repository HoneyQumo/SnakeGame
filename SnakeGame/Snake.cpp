#include "Shared/Constants.h"
#include "Snake.h"
#include "Field.h"
#include "Shared/Math.h"

namespace SnakeGame
{
    SnakeSegment CreateSnakeSegment(const sf::Vector2u& coord, const sf::Texture& texture)
    {
        SnakeSegment segment;
        segment.coord = coord;
        segment.direction = Direction::Right;
        segment.sprite.setTexture(texture);
        segment.sprite.setPosition(coord.x * CELL_WIDTH + CELL_WIDTH / 2.f, coord.y * CELL_HEIGHT + CELL_HEIGHT / 2.f);
        SetSpriteSize(segment.sprite, CELL_WIDTH, CELL_HEIGHT);
        SetSpriteOrigin(segment.sprite, 0.5f, 0.5f);

        return segment;
    }

    void MoveSnakeSegment(SnakeSegment& segment, const float speed, const float& deltaTime)
    {
        auto position = segment.sprite.getPosition();

        switch (segment.direction)
        {
        case Direction::Up:
            position.y -= speed * deltaTime;
            segment.sprite.setPosition(position);
            break;
        case Direction::Down:
            position.y += speed * deltaTime;
            segment.sprite.setPosition(position);
            break;
        case Direction::Right:
            position.x += speed * deltaTime;
            segment.sprite.setPosition(position);
            break;
        case Direction::Left:
            position.x -= speed * deltaTime;
            segment.sprite.setPosition(position);
            break;
        }
    }

    void SetSnakeSegmentCenterPosition(SnakeSegment& segment)
    {
        const auto centredPositionX = (segment.coord.x * CELL_WIDTH) + CELL_WIDTH / 2.f;
        const auto centredPositionY = (segment.coord.y * CELL_HEIGHT) + CELL_HEIGHT / 2.f;
        segment.sprite.setPosition(centredPositionX, centredPositionY);
    }

    void UpdateSnakeSegmentCoord(SnakeSegment& segment)
    {
        const auto position = segment.sprite.getPosition();

        switch (segment.direction)
        {
        case Direction::Up:
        case Direction::Down:
            segment.coord.y = static_cast<int>(position.y / CELL_HEIGHT);
            break;
        case Direction::Right:
        case Direction::Left:
            segment.coord.x = static_cast<int>(position.x / CELL_WIDTH);
            break;
        }
    }

    // void UpdateSnakeSegmentsCorner(Snake& snake)
    // {
    //     for (unsigned i = 0; i < snake.segments.size(); ++i)
    //     {
    //         SnakeSegment& segment = snake.segments[i];
    //
    //         if (i != snake.segments.size() - 1)
    //         {
    //             SnakeSegment& nextSegment = snake.segments[i + 1];
    //
    //             if (segment.direction != nextSegment.direction)
    //             {
    //                 auto& spriteColor = segment.sprite.getColor();
    //                 segment.sprite.setColor(spriteColor == sf::Color::Red ? sf::Color::White : sf::Color::Red);
    //                 nextSegment.direction = segment.direction;
    //                 UpdateSnakeSegmentRotation(segment);
    //                 break;
    //             }
    //         }
    //         else
    //         {
    //             SnakeSegment& prevSegment = snake.segments[i - 1];
    //
    //             if (segment.direction != prevSegment.direction)
    //             {
    //                 auto& spriteColor = segment.sprite.getColor();
    //                 segment.sprite.setColor(spriteColor == sf::Color::Red ? sf::Color::White : sf::Color::Red);
    //                 segment.direction = prevSegment.direction;
    //                 UpdateSnakeSegmentRotation(segment);
    //                 break;
    //             }
    //         }
    //     }
    // }

    // void UpdateSnakeSegmentsPosition(Snake& snake, const Field& field, const float& percent)
    // {
    //     for (auto& segment : snake.segments)
    //     {
    //         const auto& oldPosition = field.cells[segment.oldCoord.x][segment.oldCoord.y].shape.getPosition();
    //         const auto& newPosition = field.cells[segment.coord.x][segment.coord.y].shape.getPosition();
    //
    //         sf::Vector2f position = oldPosition + (newPosition - oldPosition) * percent;
    //         position.x += static_cast<float>(CELL_WIDTH) / 2.f;
    //         position.y += static_cast<float>(CELL_HEIGHT) / 2.f;
    //
    //         segment.sprite.setPosition(position);
    //     }
    // }

    // void UpdateSnakeSegmentsCoord(Snake& snake)
    // {
    //     for (unsigned i = 0; i < snake.segments.size(); ++i)
    //     {
    //         /* Head */
    //         if (i == 0)
    //         {
    //             SnakeSegment& head = snake.segments[i];
    //             head.oldCoord = head.coord;
    //             CalculateCoordinates(head.coord, head.direction);
    //         }
    //         /* Other segments */
    //         else
    //         {
    //             SnakeSegment& segment = snake.segments[i];
    //             const SnakeSegment& previousSegment = snake.segments[i - 1];
    //
    //             segment.oldCoord = segment.coord;
    //             CalculateCoordinates(segment.coord, segment.direction);
    //
    //             segment.coord = previousSegment.oldCoord;
    //         }
    //     }
    // }

    void UpdateSnakeSegmentRotation(SnakeSegment& segment)
    {
        switch (segment.direction)
        {
        case Direction::Up:
            segment.sprite.setRotation(270.f);
            break;
        case Direction::Down:
            segment.sprite.setRotation(90.f);
            break;
        case Direction::Right:
            segment.sprite.setRotation(0.f);
            break;
        case Direction::Left:
            segment.sprite.setRotation(180.f);
            break;
        }
    }


    void SnakeKeyboardHandler(SnakeSegment& headSegment)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            headSegment.direction = Direction::Up;
            SetSnakeSegmentCenterPosition(headSegment);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            headSegment.direction = Direction::Down;
            SetSnakeSegmentCenterPosition(headSegment);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            headSegment.direction = Direction::Right;
            SetSnakeSegmentCenterPosition(headSegment);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            headSegment.direction = Direction::Left;
            SetSnakeSegmentCenterPosition(headSegment);
        }
    }

    void InitSnake(Snake& snake)
    {
        snake.segments = {
            CreateSnakeSegment({5, 10}, snake.headTexture),
            // CreateSnakeSegment({4, 10}, snake.bodyTexture),
            // CreateSnakeSegment({3, 10}, snake.bodyTexture),
            // CreateSnakeSegment({2, 10}, snake.bodyTexture),
            // CreateSnakeSegment({1, 10}, snake.tailTexture)
        };
    }


    // void UpdateSnakeMovement(Snake& snake, const Field& field, float& movementTimer)
    // {
    //     const float timeStep = 1.f / snake.speed;
    //     const float percent = movementTimer / timeStep;
    //     
    //     if (movementTimer >= timeStep)
    //     {
    //         UpdateSnakeSegmentsCorner(snake);
    //         UpdateSnakeSegmentsCoord(snake);
    //         movementTimer -= timeStep;
    //     }
    //
    //     UpdateSnakeSegmentsPosition(snake, field, percent);
    // }

    void UpdateSnakeMovement(Snake& snake, const float& deltaTime)
    {
        SnakeSegment& headSegment = snake.segments[0];
        MoveSnakeSegment(headSegment, snake.speed, deltaTime);
        UpdateSnakeSegmentCoord(headSegment);
    }

    void DrawSnake(sf::RenderWindow& window, const Snake& snake)
    {
        for (auto& segment : snake.segments)
        {
            window.draw(segment.sprite);
        }
    }
}
