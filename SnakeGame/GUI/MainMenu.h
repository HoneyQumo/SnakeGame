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
        DifficultyLevel,
        Leaderboard,
        Settings,
        Exit
    };

    struct MainMenu
    {
        sf::Text heading;

        std::map<MainMenuOptionKey, MenuOption> options = {
            {MainMenuOptionKey::StartGame, {L"Начать игру", {}}},
            {MainMenuOptionKey::DifficultyLevel, {L"Уровень сложности", {}}},
            {MainMenuOptionKey::Leaderboard, {L"Таблица рекордов", {}}},
            {MainMenuOptionKey::Settings, {L"Настройки", {}}},
            {MainMenuOptionKey::Exit, {L"Выход", {}}},
        };

        MainMenuOptionKey selectedOptionKey = MainMenuOptionKey::StartGame;
    };

    struct Game;
    void InitMainMenu(Game& game);
    void DrawMainMenu(sf::RenderWindow& window, const MainMenu& mainMenu);

    void MainMenuOptionSelectHandler(sf::RenderWindow& window, Game& game);
    void MainMenuKeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game);
}
