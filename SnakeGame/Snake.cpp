#include "Shared/Constants.h"
#include "Snake.h"
#include "Field.h"
#include "Shared/Math.h"

namespace SnakeGame
{
    TurnPoint CreateTurnPoint(const SnakeSegment& segment, const Direction& from, const Direction& to)
    {
        TurnPoint turnPoint;
        turnPoint.position = segment.sprite.getPosition();
        turnPoint.direction = {from, to};

        return turnPoint;
    }

    void UpdateTurnPoint(SnakeSegment& segment, const sf::Vector2f& position, const float& computedDistance)
    {
        const TurnPoint& turnPoint = segment.turnPoints.front();

        const float dx = position.x - turnPoint.position.x;
        const float dy = position.y - turnPoint.position.y;
        const float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < computedDistance)
        {
            segment.direction = turnPoint.direction.to;
            UpdateSnakeSegmentRotation(segment);
            segment.turnPoints.pop();
        }
    }

    sf::RectangleShape CreateTurnPointShape(const sf::Vector2f& position, const sf::Vector2f& origin)
    {
        sf::RectangleShape tmpShape;
        tmpShape.setPosition(position.x, position.y);
        tmpShape.setOrigin(origin.x, origin.y);
        tmpShape.setSize({CELL_WIDTH, CELL_HEIGHT});
        tmpShape.setFillColor({0, 0, 0, 100});

        return tmpShape;
    }
    
    void UpdateTurnPointShape(std::vector<sf::RectangleShape>& shapes, const sf::Vector2f& position)
    {
        auto& tpShape = shapes.front();
        const auto tpShapePosition = tpShape.getPosition();
        const float dx = fabs(position.x - tpShapePosition.x);
        const float dy = fabs(position.y - tpShapePosition.y);
        if ((dx <= CELL_WIDTH / 2.f) && (dy <= CELL_HEIGHT / 2.f))
        {
            shapes.erase(shapes.begin());
        }
    }
    
    void DrawTurnPointShape(sf::RenderWindow& window, const Snake& snake)
    {
        for (auto& shape : snake.turnPointShapes)
        {
            window.draw(shape);
        }
    }

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

    void TryChangeHeadSegmentDirection(Snake& snake, const Direction newDirection)
    {
        SnakeSegment& headSegment = snake.segments[0];

        if (!HasHeadSegmentOppositeDirection(headSegment, newDirection))
        {
            const auto oldDirection = headSegment.direction;
            headSegment.direction = newDirection;
            UpdateSnakeSegmentRotation(headSegment);

            for (auto& segment : snake.segments)
            {
                SetSnakeSegmentCenterPosition(segment);
                segment.turnPoints.push(CreateTurnPoint(headSegment, oldDirection, newDirection));
            }

            snake.turnPointShapes.push_back(CreateTurnPointShape(headSegment.sprite.getPosition(), headSegment.sprite.getOrigin()));
        }
    }

    void MoveSnakeSegment(SnakeSegment& segment, sf::Vector2f& position, const float& distance)
    {
        switch (segment.direction)
        {
        case Direction::Up:
            position.y -= distance;
            segment.sprite.setPosition(position);
            break;
        case Direction::Down:
            position.y += distance;
            segment.sprite.setPosition(position);
            break;
        case Direction::Right:
            position.x += distance;
            segment.sprite.setPosition(position);
            break;
        case Direction::Left:
            position.x -= distance;
            segment.sprite.setPosition(position);
            break;
        }
    }

    void SetSnakeSegmentCenterPosition(SnakeSegment& segment)
    {
        const float centredPositionX = (segment.coord.x * CELL_WIDTH) + CELL_WIDTH / 2.f;
        const float centredPositionY = (segment.coord.y * CELL_HEIGHT) + CELL_HEIGHT / 2.f;
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


    void SnakeKeyboardHandler(Snake& snake)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            TryChangeHeadSegmentDirection(snake, Direction::Up);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            TryChangeHeadSegmentDirection(snake, Direction::Down);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            TryChangeHeadSegmentDirection(snake, Direction::Right);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            TryChangeHeadSegmentDirection(snake, Direction::Left);
        }
    }

    void InitSnake(Snake& snake)
    {
        snake.segments = {
            CreateSnakeSegment({4, 10}, snake.headTexture),
            CreateSnakeSegment({3, 10}, snake.bodyTexture),
            CreateSnakeSegment({2, 10}, snake.bodyTexture),
            CreateSnakeSegment({1, 10}, snake.tailTexture)
        };
    }

    void UpdateSnakeMovement(Snake& snake, const float& deltaTime)
    {
        const float computedDistance = snake.speed * deltaTime;

        for (unsigned i = 0; i < snake.segments.size(); ++i)
        {
            SnakeSegment& segment = snake.segments[i];
            sf::Vector2f position = segment.sprite.getPosition();

            if (!segment.turnPoints.empty())
            {
                UpdateTurnPoint(segment, position, computedDistance);
            }

            MoveSnakeSegment(segment, position, computedDistance);
            UpdateSnakeSegmentCoord(segment, position);

            if (!snake.turnPointShapes.empty() && i == snake.segments.size() - 1)
            {
                UpdateTurnPointShape(snake.turnPointShapes, position);
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
