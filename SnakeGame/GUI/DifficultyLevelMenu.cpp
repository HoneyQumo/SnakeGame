// #include "DifficultyLevelMenu.h"
#include "../Game.h"
#include "../Shared/Shared.h"

namespace SnakeGame
{
    void ResetDifficultyLevelMenu(DifficultyLevelMenu& difficultyLevelMenu)
    {
        SetOptionKey(difficultyLevelMenu.options, difficultyLevelMenu.selectedOptionKey, DifficultyLevelType::Easy);
    }

    void InitDifficultyLevelMenu(Game& game)
    {
        auto& difficultyLevelMenu = game.GUI.difficultyLevelMenu;
        ResetDifficultyLevelMenu(difficultyLevelMenu);

        InitText(difficultyLevelMenu.heading, L"..::Сложность::..", game.assets.font);
        difficultyLevelMenu.heading.setStyle(sf::Text::Underlined);
        difficultyLevelMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

        int index = 0;
        for (auto& option : difficultyLevelMenu.options)
        {
            const auto color = difficultyLevelMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White;
            InitText(option.second.textNode, option.second.title, game.assets.font, TEXT_MENU_ITEM, color);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));

            if (game.difficulty.type == option.first)
            {
                option.second.textNode.setStyle(sf::Text::Underlined);
            }

            index++;
        }
    }

    void DrawDifficultyLevelMenu(sf::RenderWindow& window, const DifficultyLevelMenu& difficultyLevelMenu)
    {
        window.draw(difficultyLevelMenu.heading);

        for (const auto& option : difficultyLevelMenu.options)
        {
            window.draw(option.second.textNode);
        }
    }

    void DifficultyLevelMenuKeyboardHandler(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                game.assets.menuSelect.play();
                game.difficulty.type = game.GUI.difficultyLevelMenu.selectedOptionKey;
                game.difficulty.value = LEVEL_CONFIG.at(game.difficulty.type);

                for (auto& option : game.GUI.difficultyLevelMenu.options)
                {
                    if (option.first == game.difficulty.type)
                    {
                        option.second.textNode.setStyle(sf::Text::Underlined);
                    }
                    else
                    {
                        option.second.textNode.setStyle(sf::Text::Regular);
                    }
                }
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(game.GUI.difficultyLevelMenu.options, game.GUI.difficultyLevelMenu.selectedOptionKey, DirectionVertical::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                game.assets.menuToggle.play();
                MenuToggleOption(game.GUI.difficultyLevelMenu.options, game.GUI.difficultyLevelMenu.selectedOptionKey, DirectionVertical::Down);
            }
        }
    }
}
