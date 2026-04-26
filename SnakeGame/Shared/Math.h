#pragma once
#include "SFML/Graphics.hpp"
#include "Constants.h"
#include "Direction.h"

namespace SnakeGame
{
    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

    void SetSpriteOrigin(sf::Sprite& sprite, float originX, float originY);

    sf::Vector2f GetNearestCenter(const sf::Vector2f& position);
    sf::Vector2i GetCoordFromPosition(const sf::Vector2f& position);

    float GetDistanceAlongDirection(const sf::Vector2f& from, const sf::Vector2f& to, Direction direction);

    bool WillCrossPoint(const sf::Vector2f& from, const sf::Vector2f& to, const sf::Vector2f& point, Direction direction);

    sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

    int GetIntegerInRange(int a, int b);
}
