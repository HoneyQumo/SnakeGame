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

        InitText(pauseMenu.heading, L"..::Пуза::..", game.assets.font);
        pauseMenu.heading.setStyle(sf::Text::Underlined);
        pauseMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        int index = 0;
        for (auto& option : pauseMenu.options)
        {
            const auto color = pauseMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
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
            game.snake.awaitingMoveInput = true;
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
                game.assets.menuSelect.play();
                PauseMenuOptionSelectHandler(game);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(game.GUI.pauseMenu.options, game.GUI.pauseMenu.selectedOptionKey, DirectionVertical::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(game.GUI.pauseMenu.options, game.GUI.pauseMenu.selectedOptionKey, DirectionVertical::Down);
            }
        }
    }
}
