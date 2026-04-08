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

    bool HasHeadSegmentOppositeDirection(const SnakeSegment& segment, const Direction direction)
    {
        if (segment.direction == direction) return true;

        if (segment.direction == Direction::Up && direction == Direction::Down) return true;
        if (segment.direction == Direction::Down && direction == Direction::Up) return true;
        if (segment.direction == Direction::Right && direction == Direction::Left) return true;
        if (segment.direction == Direction::Left && direction == Direction::Right) return true;

        return false;
    }

    void TryChangeHeadSegmentDirection(SnakeSegment& headSegment, const Direction newDirection)
    {
        if (!HasHeadSegmentOppositeDirection(headSegment, newDirection))
        {
            headSegment.direction = newDirection;
            SetSnakeSegmentCenterPosition(headSegment);
            UpdateSnakeSegmentRotation(headSegment);
        }
    }

    void MoveSnakeSegment(SnakeSegment& segment, sf::Vector2f& position, const float speed, const float& deltaTime)
    {
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

    void UpdateSnakeSegmentCoord(SnakeSegment& segment, const sf::Vector2f& position)
    {
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
            TryChangeHeadSegmentDirection(headSegment, Direction::Up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            TryChangeHeadSegmentDirection(headSegment, Direction::Down);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            TryChangeHeadSegmentDirection(headSegment, Direction::Right);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            TryChangeHeadSegmentDirection(headSegment, Direction::Left);
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

    void UpdateSnakeMovement(Snake& snake, const float& deltaTime)
    {
        for (unsigned i = 0; i < snake.segments.size(); ++i)
        {
            SnakeSegment& segment = snake.segments[i];
            sf::Vector2f position = segment.sprite.getPosition();

            MoveSnakeSegment(segment, position, snake.speed, deltaTime);
            UpdateSnakeSegmentCoord(segment, position);
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
