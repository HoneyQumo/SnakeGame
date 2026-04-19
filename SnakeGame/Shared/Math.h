#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Direction.h"

namespace SnakeGame
{
    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
    sf::Vector2f GetSpriteSize(const sf::Sprite& sprite, const sf::Vector2f& desiredSize);

    void SetSpriteOrigin(sf::Sprite& sprite, float originX, float originY);

    bool IsRectangleCollide(const sf::Vector2f& position1, const sf::Vector2f& size1, const sf::Vector2f& position2, const sf::Vector2f& size2);

    sf::Vector2f GetNearestCenter(const sf::Vector2f& position);
    sf::Vector2i GetCoordFromPosition(const sf::Vector2f& position);

    float GetDistanceAlongDirection(const sf::Vector2f& from, const sf::Vector2f& to, Direction direction);

    bool WillCrossPoint(const sf::Vector2f& from, const sf::Vector2f& to, const sf::Vector2f& point, Direction direction);

    sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

    int GetIntegerInRange(int a, int b);
}
