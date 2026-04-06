#include "Constants.h"
#include "Snake.h"
#include "Field.h"
#include "Shared/Math.h"

namespace SnakeGame
{
    SnakeSegment CreateSnakeSegment(const sf::Vector2u& coord, const sf::Texture& texture)
    {
        SnakeSegment segment;
        segment.coord = coord;
        segment.oldCoord = coord;
        segment.position = {static_cast<float>(coord.x) * CELL_WIDTH, static_cast<float>(coord.y) * CELL_HEIGHT};
        segment.sprite.setTexture(texture);
        SetSpriteSize(segment.sprite, CELL_WIDTH, CELL_HEIGHT);
        SetSpriteOrigin(segment.sprite, 0.f, 0.f);

        return segment;
    }

    void UpdateSnakeSegmentsPosition(Snake& snake, const Field& field, const float& percent)
    {
        for (auto& segment : snake.segments)
        {
            const auto& oldPosition = field.cells[segment.oldCoord.x][segment.oldCoord.y].shape.getPosition();
            const auto& newPosition = field.cells[segment.coord.x][segment.coord.y].shape.getPosition();

            segment.position = oldPosition + (newPosition - oldPosition) * percent;
        }
    }

    void UpdateSnakeSegmentsCoord(Snake& snake)
    {
        for (unsigned i = 0; i < snake.segments.size(); ++i)
        {
            snake.segments[i].oldCoord = snake.segments[i].coord;

            if (i == 0)
            {
                SnakeSegment& headSegment = snake.segments[i];

                switch (snake.direction)
                {
                case Direction::Up:
                    headSegment.coord.y--;
                    break;
                case Direction::Right:
                    headSegment.coord.x++;
                    break;
                case Direction::Down:
                    headSegment.coord.y++;
                    break;
                case Direction::Left:
                    headSegment.coord.x--;
                    break;
                }
            }
            else
            {
                SnakeSegment& segment = snake.segments[i];
                const SnakeSegment& previousSegment = snake.segments[i - 1];
                segment.coord = previousSegment.oldCoord;
            }
        }
    }

    void DrawSnakeSegment(sf::RenderWindow& window, SnakeSegment& segment)
    {
        segment.sprite.setPosition(segment.position.x, segment.position.y);
        window.draw(segment.sprite);
    }


    void SnakeKeyboardHandler(Direction& direction)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            direction = Direction::Right;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            direction = Direction::Up;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            direction = Direction::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            direction = Direction::Down;
        }
    }

    void InitSnake(Snake& snake)
    {
        snake.segments = {
            CreateSnakeSegment({5, 10}, snake.headTexture),
            CreateSnakeSegment({4, 10}, snake.bodyTexture),
            CreateSnakeSegment({3, 10}, snake.bodyTexture),
            CreateSnakeSegment({2, 10}, snake.bodyTexture),
            CreateSnakeSegment({1, 10}, snake.tailTexture)
        };
    }


    void UpdateSnakeMovement(Snake& snake, const Field& field, float& movementTimer)
    {
        const float timeStep = 1.f / snake.speed;
        const float percent = movementTimer / timeStep;

        if (movementTimer >= timeStep)
        {
            UpdateSnakeSegmentsCoord(snake);
            movementTimer -= timeStep;
        }

        UpdateSnakeSegmentsPosition(snake, field, percent);
    }

    void DrawSnake(sf::RenderWindow& window, Snake& snake)
    {
        for (auto& segment : snake.segments)
        {
            DrawSnakeSegment(window, segment);
        }
    }
}
