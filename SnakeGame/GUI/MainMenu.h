#pragma once
#include <map>
#include <string>
#include "SFML/Graphics.hpp"
#include "../Shared/Constants.h"
#include "../Shared/Math.h"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    enum class MainMenuOptionKey
    {
        StartGame = 0,
        Leaderboard,
        Settings,
        Exit
    };

    struct MainMenu
    {
        std::map<MainMenuOptionKey, MenuOption> options = {
            {MainMenuOptionKey::StartGame, {"Start Game", {}}},
            {MainMenuOptionKey::Leaderboard, {"Leaderboard", {}}},
            {MainMenuOptionKey::Settings, {"Settings", {}}},
            {MainMenuOptionKey::Exit, {"Exit", {}}},
        };

        MainMenuOptionKey selectedOptionKey = MainMenuOptionKey::StartGame;

        sf::Text heading;
    };

    struct Game;
    void InitMainMenu(Game& game);
    void DrawMainMenu(sf::RenderWindow& window, const MainMenu& mainMenu);

    void MainMenuOptionSelectHandler(sf::RenderWindow& window, Game& game);
    void MainMenuKeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game);
}
