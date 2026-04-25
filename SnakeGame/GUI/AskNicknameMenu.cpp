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

        askNicknameMenu.heading.setString(std::wstring(L"Новый рекорд!"));
        askNicknameMenu.heading.setFont(game.assets.font);
        askNicknameMenu.heading.setCharacterSize(TEXT_HEADING_1);
        askNicknameMenu.heading.setStyle(sf::Text::Underlined | sf::Text::Bold);
        askNicknameMenu.heading.setFillColor(sf::Color::White);
        askNicknameMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);
        askNicknameMenu.heading.setOrigin(GetTextOrigin(askNicknameMenu.heading, {0.5f, 0.5f}));

        askNicknameMenu.subHeading.setString(std::wstring(L"Задать имя?"));
        askNicknameMenu.subHeading.setFont(game.assets.font);
        askNicknameMenu.subHeading.setCharacterSize(TEXT_HEADING_2);
        askNicknameMenu.subHeading.setStyle(sf::Text::Bold);
        askNicknameMenu.subHeading.setFillColor(sf::Color::White);
        askNicknameMenu.subHeading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT);
        askNicknameMenu.subHeading.setOrigin(GetTextOrigin(askNicknameMenu.subHeading, {0.5f, 0.5f}));

        askNicknameMenu.nicknameText.setString(std::wstring(INPUT_PLACEHOLDER));
        askNicknameMenu.nicknameText.setFont(game.assets.font);
        askNicknameMenu.nicknameText.setCharacterSize(TEXT_HEADING_1);
        askNicknameMenu.nicknameText.setStyle(sf::Text::Italic);
        askNicknameMenu.nicknameText.setFillColor(sf::Color(50, 50, 50));
        askNicknameMenu.nicknameText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
        askNicknameMenu.nicknameText.setOrigin(GetTextOrigin(askNicknameMenu.nicknameText, {0.5f, 0.5f}));

        int index = 0;
        for (auto& option : askNicknameMenu.options)
        {
            option.second.textNode.setString(option.second.title);
            option.second.textNode.setFont(game.assets.font);
            option.second.textNode.setCharacterSize(TEXT_MENU_ITEM);
            option.second.textNode.setFillColor(askNicknameMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White);
            // option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - OFFSET_TOP_WINDOW_10_PERCENT - (askNicknameMenu.options.size() - index) * 30.f);
            option.second.textNode.setOrigin(GetTextOrigin(option.second.textNode, {0.5f, 0.5f}));

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
