#include "Shared/Constants.h"
#include "Snake.h"
#include "Field.h"
#include "Shared/Math.h"

namespace SnakeGame
{
    TurnPoint CreateTurnPoint(const sf::Vector2f& position, const Direction& direction)
    {
        TurnPoint turnPoint;
        turnPoint.position = position;
        turnPoint.direction = direction;

        return turnPoint;
    }

    sf::Sprite CreateTurnPointSprite(const sf::Texture& texture, const sf::Vector2f& position, const DirectionTurn& directionTurn)
    {
        sf::Sprite tmpSprite;
        tmpSprite.setTexture(texture);
        tmpSprite.setPosition(position.x, position.y);
        tmpSprite.setColor(sf::Color::Black);
        SetSpriteSize(tmpSprite, CELL_WIDTH, CELL_HEIGHT);
        SetSpriteOrigin(tmpSprite, 0.5f, 0.5f);

        return tmpSprite;
    }

    void UpdateTurnPointSprite(std::vector<sf::Sprite>& shapes, const sf::Vector2f& position)
    {
        const auto& tpShape = shapes.front();
        const auto& tpShapePosition = tpShape.getPosition();
        const float dx = fabs(position.x - tpShapePosition.x);
        const float dy = fabs(position.y - tpShapePosition.y);
        if ((dx <= CELL_WIDTH / 2.f) && (dy <= CELL_HEIGHT / 2.f))
        {
            shapes.erase(shapes.begin());
        }
    }

    void DrawTurnPointSprite(sf::RenderWindow& window, const Snake& snake)
    {
        for (auto& shape : snake.turnPointShapes)
        {
            window.draw(shape);
        }
    }

    SnakeSegment CreateSnakeSegment(const SegmentType& type, const sf::Vector2u& coord, const sf::Texture& texture)
    {
        SnakeSegment segment;
        segment.type = type;
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
            snake.canChangeDirection = false;
            headSegment.direction = newDirection;
            UpdateSnakeSegmentRotation(headSegment);

            const auto& headPositionCenter = GetNearestCenter(headSegment.sprite.getPosition());
            headSegment.sprite.setPosition(headPositionCenter);

            for (unsigned i = 1; i < snake.segments.size(); ++i)
            {
                auto& segment = snake.segments[i];
                segment.sprite.setPosition(GetNearestCenter(segment.sprite.getPosition()));
                segment.turnPoints.push(CreateTurnPoint(headPositionCenter, newDirection));
            }

            // const auto oldDirection = headSegment.direction;
            // snake.turnPointShapes.push_back(CreateTurnPointSprite(snake.bodyAngleTexture, headSegment.sprite.getPosition(), {oldDirection, newDirection}));
        }
    }

    void MoveSnakeSegment(SnakeSegment& segment, const float& distance)
    {
        auto position = segment.sprite.getPosition();

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

    void MoveSnakeSegmentWithTurnPoints(SnakeSegment& segment, float distance)
    {
        while (distance > 0.f)
        {
            const sf::Vector2f from = segment.sprite.getPosition();

            if (segment.turnPoints.empty())
            {
                MoveSnakeSegment(segment, distance);
                return;
            }

            const TurnPoint& turnPoint = segment.turnPoints.front();

            sf::Vector2f to = from;
            switch (segment.direction)
            {
            case Direction::Up:
                to.y -= distance;
                break;
            case Direction::Down:
                to.y += distance;
                break;
            case Direction::Right:
                to.x += distance;
                break;
            case Direction::Left:
                to.x -= distance;
                break;
            }

            if (!WillCrossPoint(from, to, turnPoint.position, segment.direction))
            {
                segment.sprite.setPosition(to);
                return;
            }

            const float distanceToTurnPoint = GetDistanceAlongDirection(from, turnPoint.position, segment.direction);
            segment.sprite.setPosition(turnPoint.position);

            segment.direction = turnPoint.direction;
            UpdateSnakeSegmentRotation(segment);
            segment.turnPoints.pop();

            distance -= distanceToTurnPoint;
        }
    }

    void UpdateSnakeSegmentCoord(SnakeSegment& segment)
    {
        const auto& position = segment.sprite.getPosition();

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

    void InitSnake(Snake& snake)
    {
        snake.segments = {
            CreateSnakeSegment(SegmentType::Head, {7, 10}, snake.headTexture),
            CreateSnakeSegment(SegmentType::Body, {6, 10}, snake.bodyTexture),
            CreateSnakeSegment(SegmentType::Body, {5, 10}, snake.bodyTexture),
            CreateSnakeSegment(SegmentType::Body, {4, 10}, snake.bodyTexture),
            CreateSnakeSegment(SegmentType::Body, {3, 10}, snake.bodyTexture),
            CreateSnakeSegment(SegmentType::Body, {2, 10}, snake.bodyTexture),
            CreateSnakeSegment(SegmentType::Tail, {1, 10}, snake.tailTexture)
        };
    }

    void UpdateSnakeMovement(Snake& snake, const float& deltaTime)
    {
        const float computedDistance = snake.speed * deltaTime;

        for (unsigned i = 0; i < snake.segments.size(); ++i)
        {
            SnakeSegment& segment = snake.segments[i];
            const auto oldCoord = segment.coord;

            if (segment.type == SegmentType::Head)
            {
                MoveSnakeSegment(segment, computedDistance);
            }
            else
            {
                MoveSnakeSegmentWithTurnPoints(segment, computedDistance);
            }

            UpdateSnakeSegmentCoord(segment);

            if (segment.type == SegmentType::Head && oldCoord != segment.coord)
            {
                snake.canChangeDirection = true;
            }

            if (!snake.turnPointShapes.empty() && segment.type == SegmentType::Tail)
            {
                const auto& position = segment.sprite.getPosition();
                UpdateTurnPointSprite(snake.turnPointShapes, position);
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
