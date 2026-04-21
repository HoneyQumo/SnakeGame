#pragma once
#include "SFML/Graphics.hpp"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    enum class GameOverMenuOptionKey
    {
        StartGame = 0,
        ExitToMainMenu
    };

    struct GameOverMenu
    {
        sf::Text heading;
        sf::Text scoreTitle;

        sf::Text recordsTitle;
        std::vector<sf::Text> leaderboard;

        std::map<GameOverMenuOptionKey, MenuOption> options = {
            {GameOverMenuOptionKey::StartGame, {L"Начать игру", {}}},
            {GameOverMenuOptionKey::ExitToMainMenu, {L"В главное меню", {}}},
        };

        GameOverMenuOptionKey selectedOptionKey = GameOverMenuOptionKey::StartGame;
    };

    void ResetGameOverMenu(GameOverMenu& gameOverMenu);
    struct Game;
    void UpdateGameOverLeaderboard(Game& game);
    void InitGameOverMenu(Game& game);
    void UpdateGameOverMenu(Game& game);
    void DrawGameOverMenu(sf::RenderWindow& window, const GameOverMenu& gameOverMenu);

    void GameOverMenuOptionSelectHandler(Game& game);
    void GameOverMenuKeyboardHandler(const sf::Event& event, Game& game);
}
