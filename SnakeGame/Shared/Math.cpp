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
}
