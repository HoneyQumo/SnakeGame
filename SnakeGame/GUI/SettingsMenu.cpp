#include "../Game.h"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    void ResetSettingsMenu(SettingsMenu& settingsMenu)
    {
        SetOptionKey(settingsMenu.options, settingsMenu.selectedOptionKey, SettingsType::Sound);
    }

    void InitSettingsMenu(Game& game)
    {
        auto& settingsMenu = game.GUI.settingsMenu;
        ResetSettingsMenu(settingsMenu);

        InitText(settingsMenu.heading, L"..::Настройки::..", game.assets.font);
        settingsMenu.heading.setStyle(sf::Text::Underlined);
        settingsMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        int index = 0;
        for (auto& option : settingsMenu.options)
        {
            const auto color = settingsMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));

            if (game.settings.states[option.first])
            {
                option.second.textNode.setStyle(sf::Text::Underlined);
            }

            index++;
        }
    }

    void DrawSettingsMenu(sf::RenderWindow& window, const SettingsMenu& settingsMenu)
    {
        window.draw(settingsMenu.heading);

        for (const auto& option : settingsMenu.options)
        {
            window.draw(option.second.textNode);
        }
    }

    void SettingsMenuOptionSelectHandler(Game& game)
    {
        auto& isSoundState = game.settings.states[SettingsType::Sound];
        auto& isMusicState = game.settings.states[SettingsType::Music];

        switch (game.GUI.settingsMenu.selectedOptionKey)
        {
        case SettingsType::Sound:
            isSoundState = !isSoundState;

            game.assets.death.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);
            game.assets.eat.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);
            game.assets.menuToggle.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);
            game.assets.menuSelect.setVolume(isSoundState ? SOUNDS_INITIAL_VOLUME : 0.f);

            break;
        case SettingsType::Music:
            isMusicState = !isMusicState;

            if (isMusicState)
            {
                game.assets.music.setVolume(MUSIC_INITIAL_VOLUME);
                game.assets.music.play();
            }
            else
            {
                game.assets.music.setVolume(0.f);
                game.assets.music.stop();
            }

            break;
        case SettingsType::ResetLeaderboard:
            ClearLeaderboard(game);
            break;
        }
    }

    void SettingsMenuKeyboardHandler(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                game.assets.menuSelect.play();

                for (auto& option : game.GUI.settingsMenu.options)
                {
                    if (option.first != SettingsType::ResetLeaderboard && option.first == game.GUI.settingsMenu.selectedOptionKey)
                    {
                        const auto& style = option.second.textNode.getStyle();
                        option.second.textNode.setStyle(style == sf::Text::Underlined ? sf::Text::Regular : sf::Text::Underlined);
                        break;
                    }
                }

                SettingsMenuOptionSelectHandler(game);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(game.GUI.settingsMenu.options, game.GUI.settingsMenu.selectedOptionKey, DirectionVertical::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(game.GUI.settingsMenu.options, game.GUI.settingsMenu.selectedOptionKey, DirectionVertical::Down);
            }
        }
    }
}
