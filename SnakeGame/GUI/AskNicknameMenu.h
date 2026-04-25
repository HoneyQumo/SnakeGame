#pragma once
#include "SFML/Graphics.hpp"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    enum class AskNicknameMenuOptionKey
    {
        Yes = 0,
        No
    };

    struct AskNicknameMenu
    {
        sf::Text heading;
        sf::Text subHeading;

        sf::String nicknameInput;
        sf::Text nicknameText;


        std::map<AskNicknameMenuOptionKey, MenuOption> options = {
            {AskNicknameMenuOptionKey::Yes, {L"Да", {}}},
            {AskNicknameMenuOptionKey::No, {L"Нет", {}}},
        };

        AskNicknameMenuOptionKey selectedOptionKey = AskNicknameMenuOptionKey::No;
    };

    void ResetAskNicknameMenu(AskNicknameMenu& askNicknameMenu);
    struct Game;
    void InitAskNicknameMenu(Game& game);
    void DrawAskNicknameMenu(sf::RenderWindow& window, const AskNicknameMenu& askNicknameMenu);

    void AskNicknameMenuKeyboardHandler(const sf::Event& event, Game& game);
}
