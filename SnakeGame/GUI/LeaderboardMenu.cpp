// #include "LeaderboardMenu.h"
#include "../Game.h"

namespace SnakeGame
{
    void UpdateLeaderboardInLeaderboardMenu(Game& game)
    {
        game.GUI.leaderboardMenu.leaderboard.clear();
        const auto& leaderboard = GetSortedLeaderboard(game.leaderboard.array);

        for (unsigned i = 0; i < leaderboard.size(); ++i)
        {
            const auto& item = leaderboard[i];

            int totalWidth = 14; // символов в строке
            int spacesNeeded = totalWidth - item.playerName.size() - item.playerName.size();

            sf::Text tmpItem;
            tmpItem.setString(std::to_wstring(i + 1) + L". " + item.playerName + std::wstring(spacesNeeded, L' ') + std::to_wstring(item.score));
            tmpItem.setFont(game.assets.font);
            tmpItem.setCharacterSize(TEXT_HEADING_3);
            tmpItem.setFillColor(sf::Color::White);
            tmpItem.setPosition(SCREEN_WIDTH / 2.f - 200.f, (OFFSET_TOP_WINDOW_20_PERCENT) + (i * 40.f));
            tmpItem.setOrigin(GetTextOrigin(tmpItem, {0.f, 0.5f}));

            game.GUI.leaderboardMenu.leaderboard.push_back(tmpItem);
        }
    }

    void InitLeaderboardMenu(Game& game)
    {
        LeaderboardMenu& leaderboardMenu = game.GUI.leaderboardMenu;

        leaderboardMenu.heading.setString(std::wstring(L"Таблица рекордов"));
        leaderboardMenu.heading.setFont(game.assets.font);
        leaderboardMenu.heading.setCharacterSize(TEXT_HEADING_1);
        leaderboardMenu.heading.setStyle(sf::Text::Bold);
        leaderboardMenu.heading.setFillColor(sf::Color::White);
        leaderboardMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);
        leaderboardMenu.heading.setOrigin(GetTextOrigin(leaderboardMenu.heading, {0.5f, 0.5f}));

        UpdateLeaderboardInLeaderboardMenu(game);
    }

    void DrawLeaderboardMenu(sf::RenderWindow& window, const LeaderboardMenu& leaderboardMenu)
    {
        window.draw(leaderboardMenu.heading);

        for (auto& item : leaderboardMenu.leaderboard)
        {
            window.draw(item);
        }
    }
}
