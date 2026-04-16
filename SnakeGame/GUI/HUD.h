#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
    struct HUD
    {
        sf::RectangleShape background;
        sf::Sprite appleSprite;
    };

    struct Game;
    void InitHUD(Game& game, const sf::Texture& appleTexture);
    void DrawHUD(sf::RenderWindow& window, const HUD& HUD);
}
