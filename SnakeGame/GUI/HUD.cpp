#include "HUD.h"
#include "../Game.h"

namespace SnakeGame
{
    void InitHUD(Game& game)
    {
        auto& HUD = game.GUI.HUD;

        HUD.background.setSize({SCREEN_WIDTH, HUD_BACKGROUND_HEIGHT});
        HUD.background.setPosition(0.f, 0.f);
        HUD.background.setFillColor(HUD_BACKGROUND_COLOR);

        HUD.appleSprite.setTexture(game.apple.texture);
        HUD.appleSprite.setPosition(10.f, HUD_BACKGROUND_HEIGHT / 2.f);
        SetSpriteSize(HUD.appleSprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteOrigin(HUD.appleSprite, 0.f, 0.5f);

        HUD.score.setString("0");
        HUD.score.setFont(game.font);
        HUD.score.setCharacterSize(30);
        HUD.score.setFillColor(sf::Color::White);
        // HUD.score.setPosition(10.f + APPLE_SIZE + 5.f, HUD_BACKGROUND_HEIGHT / 2.f);
        HUD.score.setPosition(10.f + APPLE_SIZE + 5.f, 20.f);
        HUD.score.setOrigin(GetTextOrigin(HUD.score, {0.f, 0.5f}));
    }

    void UpdateHUD(Game& game)
    {
        game.GUI.HUD.score.setString(std::to_string(game.score));
    }

    void DrawHUD(sf::RenderWindow& window, const HUD& HUD)
    {
        window.draw(HUD.background);
        window.draw(HUD.appleSprite);
        window.draw(HUD.score);
    }
}
