#include "Math.h"
#include <random>

namespace SnakeGame
{
    void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight)
    {
        const sf::FloatRect spriteRect = sprite.getLocalBounds();
        const sf::Vector2f scale = {desiredWidth / spriteRect.width, desiredHeight / spriteRect.height};
        sprite.setScale(scale);
    }

    void SetSpriteOrigin(sf::Sprite& sprite, const float originX, const float originY)
    {
        const sf::FloatRect spriteRect = sprite.getLocalBounds();
        sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
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
            static_cast<int>(position.x / CELL_WIDTH),
            static_cast<int>(position.y / CELL_HEIGHT)
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

    sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
    {
        sf::FloatRect textSize = text.getLocalBounds();
        return {
            (textSize.left + textSize.width) * relativePosition.x,
            (textSize.top + textSize.height) * relativePosition.y,
        };
    }

    int GetIntegerInRange(const int a, const int b)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(a, b);
        return dis(gen);
    }
}
