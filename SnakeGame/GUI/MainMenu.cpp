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

        mainMenu.heading.setString("..::MAIN MENU::..");
        mainMenu.heading.setFont(game.assets.font);
        mainMenu.heading.setCharacterSize(TEXT_HEADING_1);
        mainMenu.heading.setStyle(sf::Text::Underlined);
        mainMenu.heading.setFillColor(sf::Color::White);
        mainMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);
        mainMenu.heading.setOrigin(GetTextOrigin(mainMenu.heading, {0.5f, 0.5f}));

        int index = 0;
        for (auto& option : mainMenu.options)
        {
            option.second.textNode.setString(option.second.title);
            option.second.textNode.setFont(game.assets.font);
            option.second.textNode.setCharacterSize(TEXT_MENU_ITEM);
            option.second.textNode.setFillColor(mainMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
            option.second.textNode.setOrigin(GetTextOrigin(option.second.textNode, {0.5f, 0.5f}));

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
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                MenuToggleOption(game.GUI.mainMenu.options, game.GUI.mainMenu.selectedOptionKey, DirectionVertical::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                MenuToggleOption(game.GUI.mainMenu.options, game.GUI.mainMenu.selectedOptionKey, DirectionVertical::Down);
            }
        }
    }
}
