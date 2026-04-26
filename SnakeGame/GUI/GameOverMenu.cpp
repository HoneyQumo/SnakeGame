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
            const auto text = std::to_wstring(i + 1) + L". " + item.playerName + L" (" + std::to_wstring(item.score) + L")";
            InitText(tmpItem, text, game.assets.font, TEXT_MENU_ITEM, sf::Color::White, {0.f, 0.5f});
            tmpItem.setPosition(SCREEN_WIDTH / 2.f - 100.f, (SCREEN_HEIGHT / 2.f - 160.f) + (i * 30.f));

            game.GUI.gameOverMenu.leaderboard.push_back(tmpItem);
        }
    }

    void InitGameOverMenu(Game& game)
    {
        GameOverMenu& gameOverMenu = game.GUI.gameOverMenu;
        ResetGameOverMenu(gameOverMenu);

        InitText(gameOverMenu.heading, std::wstring(L"..::Количество очков::.."), game.assets.font);
        gameOverMenu.heading.setStyle(sf::Text::Bold);
        gameOverMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        InitText(gameOverMenu.scoreTitle, std::to_string(game.score), game.assets.font, TEXT_HEADING_2);
        gameOverMenu.scoreTitle.setStyle(sf::Text::Bold);
        gameOverMenu.scoreTitle.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT + 60.f);

        InitText(gameOverMenu.recordsTitle, std::wstring(L"Рекорды"), game.assets.font, TEXT_HEADING_3);
        gameOverMenu.recordsTitle.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 200.f);

        UpdateGameOverLeaderboard(game);

        int index = 0;
        for (auto& option : gameOverMenu.options)
        {
            const auto color = gameOverMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - OFFSET_TOP_WINDOW_10_PERCENT - (gameOverMenu.options.size() - index) * 30.f);
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
