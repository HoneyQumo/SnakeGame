#include "GameOverMenu.h"
#include "../Game.h"


namespace SnakeGame
{
    void ResetGameOverMenu(GameOverMenu& gameOverMenu)
    {
        SetOptionKey(gameOverMenu.options, gameOverMenu.selectedOptionKey, GameOverMenuOptionKey::StartGame);
    }

    void UpdateGameOverLeaderboard(Game& game)
    {
        game.GUI.gameOverMenu.leaderboard.clear();
        const auto& leaderboard = GetSortedLeaderboard(game.leaderboard.array);

        for (unsigned i = 0; i < std::min(5, static_cast<const int&>(leaderboard.size())); ++i)
        {
            const auto& item = leaderboard[i];

            sf::Text tmpItem;
            tmpItem.setString(std::to_wstring(i + 1) + L". " + item.playerName + L" (" + std::to_wstring(item.score) + L")");
            tmpItem.setFont(game.assets.font);
            tmpItem.setCharacterSize(20);
            tmpItem.setFillColor(sf::Color::White);
            tmpItem.setPosition(SCREEN_WIDTH / 2.f - 100.f, (SCREEN_HEIGHT / 2.f - 160.f) + (i * 30.f));
            // tmpItem.setOrigin(GetTextOrigin(tmpItem, {0.5f, 0.5f}));
            tmpItem.setOrigin(GetTextOrigin(tmpItem, {0.f, 0.5f}));

            game.GUI.gameOverMenu.leaderboard.push_back(tmpItem);
        }
    }

    void InitGameOverMenu(Game& game)
    {
        GameOverMenu& gameOverMenu = game.GUI.gameOverMenu;
        ResetGameOverMenu(gameOverMenu);

        gameOverMenu.heading.setString(std::wstring(L"Количество очков"));
        gameOverMenu.heading.setFont(game.assets.font);
        gameOverMenu.heading.setCharacterSize(TEXT_HEADING_1);
        gameOverMenu.heading.setStyle(sf::Text::Bold);
        gameOverMenu.heading.setFillColor(sf::Color::White);
        gameOverMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);
        gameOverMenu.heading.setOrigin(GetTextOrigin(gameOverMenu.heading, {0.5f, 0.5f}));

        gameOverMenu.scoreTitle.setString(std::to_string(game.score));
        gameOverMenu.scoreTitle.setFont(game.assets.font);
        gameOverMenu.scoreTitle.setCharacterSize(TEXT_HEADING_2);
        gameOverMenu.scoreTitle.setStyle(sf::Text::Bold);
        gameOverMenu.scoreTitle.setFillColor(sf::Color::White);
        gameOverMenu.scoreTitle.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT + 60.f);
        gameOverMenu.scoreTitle.setOrigin(GetTextOrigin(gameOverMenu.scoreTitle, {0.5f, 0.5f}));

        gameOverMenu.recordsTitle.setString(std::wstring(L"Рекорды"));
        gameOverMenu.recordsTitle.setFont(game.assets.font);
        gameOverMenu.recordsTitle.setCharacterSize(TEXT_HEADING_3);
        gameOverMenu.recordsTitle.setFillColor(sf::Color::White);
        gameOverMenu.recordsTitle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 200.f);
        gameOverMenu.recordsTitle.setOrigin(GetTextOrigin(gameOverMenu.recordsTitle, {0.5f, 0.5f}));

        UpdateGameOverLeaderboard(game);

        int index = 0;
        for (auto& option : gameOverMenu.options)
        {
            option.second.textNode.setString(option.second.title);
            option.second.textNode.setFont(game.assets.font);
            option.second.textNode.setCharacterSize(TEXT_MENU_ITEM);
            option.second.textNode.setFillColor(gameOverMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White);
            // option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - OFFSET_TOP_WINDOW_10_PERCENT - (gameOverMenu.options.size() - index) * 30.f);
            option.second.textNode.setOrigin(GetTextOrigin(option.second.textNode, {0.5f, 0.5f}));

            index++;
        }
    }

    void UpdateGameOverMenu(Game& game)
    {
        GameOverMenu& gameOverMenu = game.GUI.gameOverMenu;

        gameOverMenu.scoreTitle.setString(std::to_string(game.score));
    }

    void DrawGameOverMenu(sf::RenderWindow& window, const GameOverMenu& gameOverMenu)
    {
        window.draw(gameOverMenu.heading);
        window.draw(gameOverMenu.scoreTitle);
        window.draw(gameOverMenu.recordsTitle);

        for (const auto& item : gameOverMenu.leaderboard)
        {
            window.draw(item);
        }

        for (const auto& option : gameOverMenu.options)
        {
            window.draw(option.second.textNode);
        }
    }

    void GameOverMenuOptionSelectHandler(Game& game)
    {
        switch (game.GUI.gameOverMenu.selectedOptionKey)
        {
        case GameOverMenuOptionKey::StartGame:
            ResetGame(game);
            SwitchGameState(game, GameState::Playing);
            break;
        case GameOverMenuOptionKey::ExitToMainMenu:
            ResetGame(game);
            break;
        }
    }

    void GameOverMenuKeyboardHandler(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                game.assets.menuSelect.play();
                GameOverMenuOptionSelectHandler(game);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(game.GUI.gameOverMenu.options, game.GUI.gameOverMenu.selectedOptionKey, DirectionVertical::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(game.GUI.gameOverMenu.options, game.GUI.gameOverMenu.selectedOptionKey, DirectionVertical::Down);
            }
        }
    }
}
