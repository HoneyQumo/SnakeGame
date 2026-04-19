#include "Apple.h"
#include "Game.h"

namespace SnakeGame
{
    Apple CreateApple(const sf::Texture& texture, const sf::Vector2f& position)
    {
        Apple apple;
        apple.sprite.setTexture(texture);
        apple.sprite.setPosition(position.x, position.y);
        SetSpriteSize(apple.sprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteOrigin(apple.sprite, 0.5f, 0.5f);
        return apple;
    }

    void DrawApples(sf::RenderWindow& window, const std::vector<Apple>& apples)
    {
        for (auto& apple : apples)
        {
            window.draw(apple.sprite);
        }
    }

    void SpawnApple(Game& game)
    {
        const auto availableCoords = GetAvailableCoords(game);
        const int randomIndex = GetIntegerInRange(0, static_cast<int>(availableCoords.size()) - 1);
        const auto randomCoord = availableCoords[randomIndex];

        const sf::Vector2f position{
            static_cast<float>(randomCoord.x * CELL_WIDTH) + CELL_WIDTH / 2.f,
            static_cast<float>(randomCoord.y * CELL_HEIGHT) + CELL_HEIGHT / 2.f,
        };

        game.apples.push_back(CreateApple(game.assets.apple, position));
    }
}
