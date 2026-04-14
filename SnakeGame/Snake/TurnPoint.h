#pragma once
#include "./Snake.h"

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
    void DrawTurnPointSprite(sf::RenderWindow& window, const Snake& snake);
}
