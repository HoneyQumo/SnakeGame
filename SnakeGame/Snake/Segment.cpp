#include "Segment.h"
#include "Snake.h"

namespace SnakeGame
{
    Segment CreateSegment(const SegmentType& type, const sf::Vector2u& coord, const sf::Texture& texture)
    {
        Segment segment;

        segment.type = type;
        segment.direction = Direction::Right;
        segment.sprite.setTexture(texture);
        segment.sprite.setPosition(coord.x * CELL_WIDTH + CELL_WIDTH / 2.f, coord.y * CELL_HEIGHT + CELL_HEIGHT / 2.f);
        SetSpriteSize(segment.sprite, CELL_WIDTH, CELL_HEIGHT);
        SetSpriteOrigin(segment.sprite, 0.5f, 0.5f);

        return segment;
    }

    bool HasHeadSegmentOppositeDirection(const Segment& segment, const Direction direction)
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
        Segment& headSegment = snake.segments[0];

        if (!HasHeadSegmentOppositeDirection(headSegment, newDirection))
        {
            snake.canChangeDirection = false;
            headSegment.direction = newDirection;
            UpdateSegmentRotation(headSegment);

            const auto& headPositionCenter = GetNearestCenter(headSegment.sprite.getPosition());
            headSegment.sprite.setPosition(headPositionCenter);

            for (unsigned i = 1; i < snake.segments.size(); ++i)
            {
                auto& segment = snake.segments[i];
                segment.sprite.setPosition(GetNearestCenter(segment.sprite.getPosition()));
                segment.turnPoints.push(CreateTurnPoint(headPositionCenter, newDirection));
            }

            // const auto oldDirection = headSegment.direction;
            // snake.turnPointSprite.push_back(CreateTurnPointSprite(snake.bodyAngleTexture, headSegment.sprite.getPosition(), {oldDirection, newDirection}));
        }
    }

    void MoveSegment(Segment& segment, const float& distance)
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

    void MoveSegmentWithTurnPoints(Segment& segment, float distance)
    {
        while (distance > 0.f)
        {
            const sf::Vector2f from = segment.sprite.getPosition();

            if (segment.turnPoints.empty())
            {
                MoveSegment(segment, distance);
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
            UpdateSegmentRotation(segment);
            segment.turnPoints.pop();

            distance -= distanceToTurnPoint;
        }
    }

    void UpdateSegmentRotation(Segment& segment)
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
}
