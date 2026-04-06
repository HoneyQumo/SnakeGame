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
        segment.oldCoord = coord;
        segment.direction = {1, 0};
        segment.sprite.setTexture(texture);
        segment.sprite.setPosition(coord.x * CELL_WIDTH + CELL_WIDTH / 2.f, coord.y * CELL_HEIGHT + CELL_HEIGHT / 2.f);
        SetSpriteSize(segment.sprite, CELL_WIDTH, CELL_HEIGHT);
        SetSpriteOrigin(segment.sprite, 0.5f, 0.5f);

        return segment;
    }

    void UpdateSnakeSegmentsPosition(Snake& snake, const Field& field, const float& percent)
    {
        for (auto& segment : snake.segments)
        {
            const auto& oldPosition = field.cells[segment.oldCoord.x][segment.oldCoord.y].shape.getPosition();
            const auto& newPosition = field.cells[segment.coord.x][segment.coord.y].shape.getPosition();

            sf::Vector2f position = oldPosition + (newPosition - oldPosition) * percent;
            position.x += static_cast<float>(CELL_WIDTH) / 2.f;
            position.y += static_cast<float>(CELL_HEIGHT) / 2.f;

            segment.sprite.setPosition(position);
        }
    }

    void UpdateSnakeSegmentsCoord(Snake& snake)
    {
        for (unsigned i = 0; i < snake.segments.size(); ++i)
        {
            SnakeSegment& segment = snake.segments[i];
            segment.oldCoord = segment.coord;
            CalculateCoordinates(segment.coord, segment.direction);

            if (i == 0) continue;

            const SnakeSegment& previousSegment = snake.segments[i - 1];
            segment.direction = previousSegment.direction;
            segment.coord = previousSegment.oldCoord;
        }
    }

    void UpdateSnakeSegmentRotation(SnakeSegment& segment)
    {
        if (segment.direction.y == -1)
        {
            segment.sprite.setRotation(270.f);
        }
        else if (segment.direction.y == 1)
        {
            segment.sprite.setRotation(90.f);
        }
        else if (segment.direction.x == 1)
        {
            segment.sprite.setRotation(0.f);
        }
        else if (segment.direction.x == -1)
        {
            segment.sprite.setRotation(180.f);
        }
    }

    void DrawSnakeSegment(sf::RenderWindow& window, const SnakeSegment& segment)
    {
        window.draw(segment.sprite);
    }


    void SnakeKeyboardHandler(SnakeSegment& headSegment)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            headSegment.direction = {0, -1};
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            headSegment.direction = {0, 1};
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            headSegment.direction = {1, 0};
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            headSegment.direction = {-1, 0};
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
            UpdateSnakeSegmentRotation(segment);
            DrawSnakeSegment(window, segment);
        }
    }
}
