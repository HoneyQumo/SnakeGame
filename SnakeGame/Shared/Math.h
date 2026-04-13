#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
    sf::Vector2f GetSpriteSize(const sf::Sprite& sprite, const sf::Vector2f& desiredSize);

    void SetSpriteOrigin(sf::Sprite& sprite, float originX, float originY);

    bool IsRectangleCollide(const sf::Vector2f& position1, const sf::Vector2f& size1, const sf::Vector2f& position2, const sf::Vector2f& size2);
}
