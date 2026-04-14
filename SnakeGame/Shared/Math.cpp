#include "Math.h"

namespace SnakeGame
{
    void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight)
    {
        const sf::FloatRect spriteRect = sprite.getLocalBounds();
        const sf::Vector2f scale = {desiredWidth / spriteRect.width, desiredHeight / spriteRect.height};
        sprite.setScale(scale);
    }

    sf::Vector2f GetSpriteSize(const sf::Sprite& sprite, const sf::Vector2f& desiredSize)
    {
        const sf::Vector2u textureSize = sprite.getTexture()->getSize();
        const sf::Vector2f scale = {desiredSize.x / static_cast<float>(textureSize.x), desiredSize.y / static_cast<float>(textureSize.y)};
        return scale;
    }

    void SetSpriteOrigin(sf::Sprite& sprite, const float originX, const float originY)
    {
        const sf::FloatRect spriteRect = sprite.getLocalBounds();
        sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
    }


    bool IsRectangleCollide(const sf::Vector2f& position1, const sf::Vector2f& size1, const sf::Vector2f& position2, const sf::Vector2f& size2)
    {
        const float halfColliderSumX = (size1.x + size2.x) / 2.f;
        const float halfColliderSumY = (size1.y + size2.y) / 2.f;

        const float deltaX = fabs(position1.x - position2.x);
        const float deltaY = fabs(position1.y - position2.y);

        return deltaX <= halfColliderSumX && deltaY <= halfColliderSumY;
    }

    sf::Vector2f GetNearestCenter(const sf::Vector2f& position)
    {
        const float fx = (position.x - CELL_WIDTH / 2.f) / CELL_WIDTH;
        const float fy = (position.y - CELL_HEIGHT / 2.f) / CELL_HEIGHT;
        const float ix = std::round(fx);
        const float iy = std::round(fy);
        return {
            ix * CELL_WIDTH + CELL_WIDTH / 2.f,
            iy * CELL_HEIGHT + CELL_HEIGHT / 2.f
        };
    }

    sf::Vector2i GetCoordFromPosition(const sf::Vector2f& position)
    {
        return sf::Vector2i{
            static_cast<int>(position.y / CELL_HEIGHT),
            static_cast<int>(position.x / CELL_WIDTH)
        };
    }

    float GetDistanceAlongDirection(const sf::Vector2f& from, const sf::Vector2f& to, const Direction direction)
    {
        switch (direction)
        {
        case Direction::Up:
        case Direction::Down:
            return std::abs(to.y - from.y);
        case Direction::Left:
        case Direction::Right:
            return std::abs(to.x - from.x);
        }
        return 0.f;
    }

    bool WillCrossPoint(const sf::Vector2f& from, const sf::Vector2f& to, const sf::Vector2f& point, const Direction direction)
    {
        if (direction == Direction::Up || direction == Direction::Down)
        {
            if (std::abs(from.x - point.x) > CELL_WIDTH / 2.f) return false;
            if (std::abs(to.x - point.x) > CELL_WIDTH / 2.f) return false;

            const float minY = std::min(from.y, to.y) - EPSILON;
            const float maxY = std::max(from.y, to.y) + EPSILON;

            return (point.y >= minY) && (point.y <= maxY);
        }

        if (direction == Direction::Left || direction == Direction::Right)
        {
            if (std::abs(from.y - point.y) > CELL_HEIGHT / 2.f) return false;
            if (std::abs(to.y - point.y) > CELL_HEIGHT / 2.f) return false;

            const float minX = std::min(from.x, to.x) - EPSILON;
            const float maxX = std::max(from.x, to.x) + EPSILON;

            return (point.x >= minX) && (point.x <= maxX);
        }
    }
}
