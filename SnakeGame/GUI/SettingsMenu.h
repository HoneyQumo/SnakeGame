#pragma once
#include "SFML/Graphics.hpp"
#include "../Settings.h"
#include "../DifficultyLevel.h"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    struct SettingsMenu
    {
        sf::Text heading;

        std::map<SettingsType, MenuOption> options = {
            {SettingsType::Sound, {L"Звук", {}}},
            {SettingsType::Music, {L"Музыка", {}}},
            {SettingsType::ResetLeaderboard, {L"Сбросить рекорды", {}}},
        };

        SettingsType selectedOptionKey = SettingsType::Sound;
    };

    struct Game;
    void ResetSettingsMenu(SettingsMenu& settingsMenu);
    void InitSettingsMenu(Game& game);
    void DrawSettingsMenu(sf::RenderWindow& window, const SettingsMenu& settingsMenu);

    void SettingsMenuOptionSelectHandler(Game& game);
    void SettingsMenuKeyboardHandler(const sf::Event& event, Game& game);
}
