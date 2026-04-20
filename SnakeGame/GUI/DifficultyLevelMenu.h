#pragma once
#include "SFML/Graphics.hpp"
#include "../DifficultyLevel.h"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    struct DifficultyLevelMenu
    {
        sf::Text heading;

        std::map<DifficultyLevelType, MenuOption> options = {
            {DifficultyLevelType::Easy, {L"Простой", {}}},
            {DifficultyLevelType::EasyMedium, {L"Тяжелее простого", {}}},
            {DifficultyLevelType::Medium, {L"Средний", {}}},
            {DifficultyLevelType::MediumHard, {L"Легче тяжелого", {}}},
            {DifficultyLevelType::Hard, {L"Тяжелый", {}}},
        };

        DifficultyLevelType selectedOptionKey = DifficultyLevelType::Easy;
    };

    void ResetDifficultyLevelMenu(DifficultyLevelMenu& difficultyLevelMenu);
    struct Game;
    void InitDifficultyLevelMenu(Game& game);
    void DrawDifficultyLevelMenu(sf::RenderWindow& window, const DifficultyLevelMenu& difficultyLevelMenu);

    void DifficultyLevelMenuKeyboardHandler(const sf::Event& event, Game& game);
}
