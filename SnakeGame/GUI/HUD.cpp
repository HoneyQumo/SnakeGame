#include "HUD.h"
#include "../Game.h"

namespace SnakeGame
{
    void InitHUD(Game& game, const sf::Texture& appleTexture)
    {
        game.GUI.HUD.background.setSize({SCREEN_WIDTH, HUD_BACKGROUND_HEIGHT});
        game.GUI.HUD.background.setPosition(0.f, 0.f);
        game.GUI.HUD.background.setFillColor(HUD_BACKGROUND_COLOR);

        game.GUI.HUD.appleSprite.setTexture(appleTexture);
        game.GUI.HUD.appleSprite.setPosition(10.f, HUD_BACKGROUND_HEIGHT / 2.f);
        SetSpriteSize(game.GUI.HUD.appleSprite, APPLE_SIZE, APPLE_SIZE);
        SetSpriteOrigin(game.GUI.HUD.appleSprite, 0.f, 0.5f);
    }

    void DrawHUD(sf::RenderWindow& window, const HUD& HUD)
    {
        window.draw(HUD.background);
        window.draw(HUD.appleSprite);
    }
}
