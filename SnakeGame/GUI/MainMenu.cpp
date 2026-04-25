#include "../Game.h"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    void ResetMainMenu(MainMenu& mainMenu)
    {
        SetOptionKey(mainMenu.options, mainMenu.selectedOptionKey, MainMenuOptionKey::StartGame);
    }

    void InitMainMenu(Game& game)
    {
        MainMenu& mainMenu = game.GUI.mainMenu;
        ResetMainMenu(mainMenu);

        InitText(mainMenu.heading, "..::MAIN MENU::..", game.assets.font);
        mainMenu.heading.setStyle(sf::Text::Underlined);
        mainMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        int index = 0;
        for (auto& option : mainMenu.options)
        {
            const auto color = mainMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
            index++;
        }
    }

    void DrawMainMenu(sf::RenderWindow& window, const MainMenu& mainMenu)
    {
        window.draw(mainMenu.heading);

        for (const auto& option : mainMenu.options)
        {
            window.draw(option.second.textNode);
        }
    }

    void MainMenuOptionSelectHandler(sf::RenderWindow& window, Game& game)
    {
        switch (game.GUI.mainMenu.selectedOptionKey)
        {
        case MainMenuOptionKey::StartGame:
            SwitchGameState(game, GameState::Playing);
            break;
        case MainMenuOptionKey::DifficultyLevel:
            PushGameState(game, GameState::DifficultyLevel);
            break;
        case MainMenuOptionKey::Leaderboard:
            UpdateLeaderboardInLeaderboardMenu(game);
            PushGameState(game, GameState::Leaderboard);
            break;
        case MainMenuOptionKey::Settings:
            PushGameState(game, GameState::Settings);
            break;
        case MainMenuOptionKey::Exit:
            window.close();
            break;
        }
    }

    void MainMenuKeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                MainMenuOptionSelectHandler(window, game);
                game.assets.menuSelect.play();
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                MenuToggleOption(game.GUI.mainMenu.options, game.GUI.mainMenu.selectedOptionKey, DirectionVertical::Up);
                game.assets.menuToggle.play();
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                MenuToggleOption(game.GUI.mainMenu.options, game.GUI.mainMenu.selectedOptionKey, DirectionVertical::Down);
                game.assets.menuToggle.play();
            }
        }
    }
}
