#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "../Shared/Direction.h"
#include "../Shared/Math.h"

namespace SnakeGame
{
    struct TurnPoint
    {
        sf::Vector2f position;
        Direction direction;
    };

    TurnPoint CreateTurnPoint(const sf::Vector2f& position, const Direction& direction);

    /* Sprite */
    sf::Sprite CreateTurnPointSprite(const sf::Texture& texture, const sf::Vector2f& position, const DirectionTurn& directionTurn);
    void UpdateTurnPointSprite(std::vector<sf::Sprite>& shapes, const sf::Vector2f& position);

    struct Snake;
    void DrawTurnPointSprite(sf::RenderWindow& window, const Snake& snake);
}
