#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
    struct HUD
    {
        sf::RectangleShape background;
        sf::Sprite appleSprite;

        sf::Text score;
    };


    struct Game;
    void InitHUD(Game& game);
    void UpdateHUD(Game& game);
    void DrawHUD(sf::RenderWindow& window, const HUD& HUD);
}
