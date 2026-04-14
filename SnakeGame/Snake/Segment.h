#pragma once
#include <queue>
#include "SFML/Graphics.hpp"
#include "./TurnPoint.h"
#include "../Shared/Direction.h"
#include "../Shared/Math.h"

namespace SnakeGame
{
    enum class SegmentType
    {
        Head = 0,
        Body,
        Tail
    };

    struct Segment
    {
        SegmentType type;
        Direction direction;
        sf::Sprite sprite;
        std::queue<TurnPoint> turnPoints;
    };


    Segment CreateSegment(const SegmentType& type, const sf::Vector2u& coord, const sf::Texture& texture);

    bool HasHeadSegmentOppositeDirection(const Segment& segment, Direction direction);

    struct Snake;
    void TryChangeHeadSegmentDirection(Snake& snake, Direction newDirection);

    void MoveSegment(Segment& segment, const float& distance);
    void MoveSegmentWithTurnPoints(Segment& segment, float distance);

    void UpdateSegmentRotation(Segment& segment);
}
