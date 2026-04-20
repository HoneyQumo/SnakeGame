#include "PauseMenu.h"
#include "../Game.h"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    void ResetPauseMenu(PauseMenu& pauseMenu)
    {
        SetOptionKey(pauseMenu.options, pauseMenu.selectedOptionKey, PauseMenuOptionKey::Continue);
    }

    void InitPauseMenu(Game& game)
    {
        auto& pauseMenu = game.GUI.pauseMenu;
        ResetPauseMenu(pauseMenu);

        pauseMenu.heading.setString("..::Pause::..");
        pauseMenu.heading.setFont(game.assets.font);
        pauseMenu.heading.setCharacterSize(TEXT_HEADING_1);
        pauseMenu.heading.setStyle(sf::Text::Underlined);
        pauseMenu.heading.setFillColor(sf::Color::White);
        pauseMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);
        pauseMenu.heading.setOrigin(GetTextOrigin(pauseMenu.heading, {0.5f, 0.5f}));

        int index = 0;
        for (auto& option : pauseMenu.options)
        {
            option.second.textNode.setString(option.second.title);
            option.second.textNode.setFont(game.assets.font);
            option.second.textNode.setCharacterSize(TEXT_MENU_ITEM);
            option.second.textNode.setFillColor(pauseMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
            option.second.textNode.setOrigin(GetTextOrigin(option.second.textNode, {0.5f, 0.5f}));

            index++;
        }
    }

    void DrawPauseMenu(sf::RenderWindow& window, const PauseMenu& pauseMenu)
    {
        window.draw(pauseMenu.heading);

        for (const auto& option : pauseMenu.options)
        {
            window.draw(option.second.textNode);
        }
    }

    void PauseMenuOptionSelectHandler(Game& game)
    {
        switch (game.GUI.pauseMenu.selectedOptionKey)
        {
        case PauseMenuOptionKey::Continue:
            PopGameState(game);
            break;
        case PauseMenuOptionKey::Exit:
            ResetGame(game);
            SwitchGameState(game, GameState::MainMenu);
            break;
        }
    }

    void PauseMenuKeyboardHandler(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                PauseMenuOptionSelectHandler(game);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                MenuToggleOption(game.GUI.pauseMenu.options, game.GUI.pauseMenu.selectedOptionKey, DirectionVertical::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                MenuToggleOption(game.GUI.pauseMenu.options, game.GUI.pauseMenu.selectedOptionKey, DirectionVertical::Down);
            }
        }
    }
}
