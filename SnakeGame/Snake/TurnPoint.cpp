#include "TurnPoint.h"

namespace SnakeGame
{
    TurnPoint CreateTurnPoint(const sf::Vector2f& position, const Direction& direction)
    {
        TurnPoint turnPoint;
        turnPoint.position = position;
        turnPoint.direction = direction;

        return turnPoint;
    }

    sf::Sprite CreateTurnPointSprite(const sf::Texture& texture, const sf::Vector2f& position, const DirectionTurn& directionTurn)
    {
        sf::Sprite tmpSprite;
        tmpSprite.setTexture(texture);
        tmpSprite.setPosition(position.x, position.y);
        tmpSprite.setColor(sf::Color::Black);
        SetSpriteSize(tmpSprite, CELL_WIDTH, CELL_HEIGHT);
        SetSpriteOrigin(tmpSprite, 0.5f, 0.5f);

        return tmpSprite;
    }

    void UpdateTurnPointSprite(std::vector<sf::Sprite>& shapes, const sf::Vector2f& position)
    {
        const auto& tpShape = shapes.front();
        const auto& tpShapePosition = tpShape.getPosition();
        const float dx = fabs(position.x - tpShapePosition.x);
        const float dy = fabs(position.y - tpShapePosition.y);
        if ((dx <= CELL_WIDTH / 2.f) && (dy <= CELL_HEIGHT / 2.f))
        {
            shapes.erase(shapes.begin());
        }
    }

    void DrawTurnPointSprite(sf::RenderWindow& window, const Snake& snake)
    {
        for (auto& shape : snake.turnPointSprite)
        {
            window.draw(shape);
        }
    }
}
