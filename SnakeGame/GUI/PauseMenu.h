#pragma once
#include <map>
#include "SFML/Graphics.hpp"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    enum class PauseMenuOptionKey
    {
        Continue = 0,
        Exit,
    };

    struct PauseMenu
    {
        sf::Text heading;

        std::map<PauseMenuOptionKey, MenuOption> options = {
            {PauseMenuOptionKey::Continue, {L"Продолжить", {}}},
            {PauseMenuOptionKey::Exit, {L"Выйти в меню", {}}},
        };

        PauseMenuOptionKey selectedOptionKey = PauseMenuOptionKey::Continue;
    };

    struct Game;
    void ResetPauseMenu(PauseMenu& pauseMenu);
    void InitPauseMenu(Game& game);
    void DrawPauseMenu(sf::RenderWindow& window, const PauseMenu& pauseMenu);

    void PauseMenuOptionSelectHandler(Game& game);
    void PauseMenuKeyboardHandler(const sf::Event& event, Game& game);
}
