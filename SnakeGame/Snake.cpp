#include "Shared/Constants.h"
#include "Snake.h"
#include "Field.h"
#include "Shared/Math.h"

namespace SnakeGame
{
    TurnPoint CreateTurnPoint(const SnakeSegment& segment, const Direction& direction)
    {
        TurnPoint turnPoint;
        turnPoint.position = segment.sprite.getPosition();
        turnPoint.direction = direction;
        
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
            segment.direction = turnPoint.direction;
            UpdateSnakeSegmentRotation(segment);
            segment.turnPoints.pop();
        }
    }

    sf::Sprite CreateTurnPointSprite(const sf::Texture& texture, const sf::Vector2f& position, const DirectionTurn& directionTurn)
    {
        sf::Sprite tmpSprite;
        tmpSprite.setTexture(texture);
        tmpSprite.setPosition(position.x, position.y);
        tmpSprite.setColor(sf::Color::Black);
        SetSpriteSize(tmpSprite, CELL_WIDTH, CELL_HEIGHT);
        SetSpriteOrigin(tmpSprite, 0.5f, 0.5f);

        // SetTurnPointSpriteRotation(tmpSprite, directionTurn);

        return tmpSprite;
    }

    void UpdateTurnPointSprite(std::vector<sf::Sprite>& shapes, const sf::Vector2f& position)
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

    // void SetTurnPointSpriteRotation(sf::Sprite& sprite, const DirectionTurn& directionTurn)
    // {
    //     const auto& from = directionTurn.from;
    //     const auto& to = directionTurn.to;
    //
    //     auto isPair = [&](Direction d1, Direction d2)
    //     {
    //         return (from == d1 && to == d2) || (from == d2 && to == d1);
    //     };
    //
    //     // if (isPair(Direction::Up, Direction::Right))
    //     // {
    //     //     sprite.setRotation(0.f);
    //     // }
    //     // else if (isPair(Direction::Up, Direction::Left))
    //     // {
    //     //     const auto& scale = sprite.getScale();
    //     //     sprite.setRotation(90.f);
    //     //     sprite.setScale(-scale.x, scale.y);
    //     // }
    //     // else if (isPair(Direction::Down, Direction::Right))
    //     // {
    //     //     const auto& scale = sprite.getScale();
    //     //     sprite.setRotation(0.f);
    //     //     sprite.setScale(scale.x, -scale.y);
    //     // }
    //     // else if (isPair(Direction::Down, Direction::Left))
    //     // {
    //     //     sprite.setRotation(180.f);
    //     // }
    //
    //     // if (isPair(Direction::Left, Direction::Down)) sprite.setRotation(0.f);
    //     // if (isPair(Direction::Left, Direction::Up)) sprite.setRotation(90.f);
    //     // if (isPair(Direction::Right, Direction::Up)) sprite.setRotation(180.f);
    //     // if (isPair(Direction::Right, Direction::Down)) sprite.setRotation(270.f);
    // }

    void DrawTurnPointSprite(sf::RenderWindow& window, const Snake& snake)
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
                segment.turnPoints.push(CreateTurnPoint(headSegment, newDirection));
            }

            // snake.turnPointShapes.push_back(CreateTurnPointSprite(snake.bodyAngleTexture, headSegment.sprite.getPosition(), {oldDirection, newDirection}));
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
