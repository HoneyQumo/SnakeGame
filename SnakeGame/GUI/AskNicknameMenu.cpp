#include "AskNicknameMenu.h"
#include "../Game.h"


namespace SnakeGame
{
    void ResetAskNicknameMenu(AskNicknameMenu& askNicknameMenu)
    {
        askNicknameMenu.nicknameInput.clear();
        SetOptionKey(askNicknameMenu.options, askNicknameMenu.selectedOptionKey, AskNicknameMenuOptionKey::Yes);
    }

    void InitAskNicknameMenu(Game& game)
    {
        AskNicknameMenu& askNicknameMenu = game.GUI.askNicknameMenu;
        ResetAskNicknameMenu(askNicknameMenu);

        InitText(askNicknameMenu.heading, std::wstring(L"..::Новый рекорд!::.."), game.assets.font);
        askNicknameMenu.heading.setStyle(sf::Text::Underlined | sf::Text::Bold);
        askNicknameMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        InitText(askNicknameMenu.subHeading, std::wstring(L"Задать имя?"), game.assets.font, TEXT_HEADING_2);
        askNicknameMenu.subHeading.setStyle(sf::Text::Bold);
        askNicknameMenu.subHeading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT);

        InitText(askNicknameMenu.nicknameText, std::wstring(INPUT_PLACEHOLDER), game.assets.font, TEXT_HEADING_1, sf::Color(50, 50, 50));
        askNicknameMenu.nicknameText.setStyle(sf::Text::Italic);
        askNicknameMenu.nicknameText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

        int index = 0;
        for (auto& option : askNicknameMenu.options)
        {
            const auto color = askNicknameMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - OFFSET_TOP_WINDOW_10_PERCENT - (askNicknameMenu.options.size() - index) * 30.f);
            index++;
        }
    }


    void DrawAskNicknameMenu(sf::RenderWindow& window, const AskNicknameMenu& askNicknameMenu)
    {
        window.draw(askNicknameMenu.heading);
        window.draw(askNicknameMenu.subHeading);
        window.draw(askNicknameMenu.nicknameText);

        for (const auto& option : askNicknameMenu.options)
        {
            window.draw(option.second.textNode);
        }
    }


    void AskNicknameMenuKeyboardHandler(const sf::Event& event, Game& game)
    {
        auto& askNicknameMenu = game.GUI.askNicknameMenu;

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                game.assets.menuSelect.play();
                AddItemToLeaderboard(game);
                UpdateGameOverLeaderboard(game);
                SerializeAndSaveGame(game.leaderboard);
                PopGameState(game);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(askNicknameMenu.options, askNicknameMenu.selectedOptionKey, DirectionVertical::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(askNicknameMenu.options, askNicknameMenu.selectedOptionKey, DirectionVertical::Down);
            }
        }

        if (event.type == sf::Event::TextEntered)
        {
            if (askNicknameMenu.nicknameInput == INPUT_PLACEHOLDER)
            {
                askNicknameMenu.nicknameInput.clear();
            }

            if (event.text.unicode == 8)
            {
                if (!askNicknameMenu.nicknameInput.isEmpty())
                {
                    askNicknameMenu.nicknameInput.erase(askNicknameMenu.nicknameInput.getSize() - 1);
                }
            }
            else if (event.text.unicode < 128 || (event.text.unicode >= 1024 && event.text.unicode <= 1279))
            {
                if (askNicknameMenu.nicknameInput.getSize() < 20)
                {
                    askNicknameMenu.nicknameInput += event.text.unicode;
                }
            }

            if (askNicknameMenu.nicknameInput.isEmpty())
            {
                askNicknameMenu.nicknameInput = INPUT_PLACEHOLDER;
                askNicknameMenu.nicknameText.setFillColor(sf::Color(50, 50, 50));
            }
            else
            {
                askNicknameMenu.nicknameText.setFillColor(sf::Color::White);
            }

            askNicknameMenu.nicknameText.setString(askNicknameMenu.nicknameInput.toWideString());
            askNicknameMenu.nicknameText.setOrigin(GetTextOrigin(askNicknameMenu.nicknameText, {0.5f, 0.5f}));
        }
    }
}
