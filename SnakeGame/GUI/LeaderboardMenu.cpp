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

            sf::Text tmpItem;
            const auto text = std::to_wstring(i + 1) + L". " + item.playerName + L" (" + std::to_wstring(item.score) + L")";
            InitText(tmpItem, text, game.assets.font, TEXT_HEADING_3, sf::Color::White, {0.f, 0.5f});
            tmpItem.setPosition(SCREEN_WIDTH / 2.f - 200.f, (OFFSET_TOP_WINDOW_20_PERCENT) + (i * 40.f));

            game.GUI.leaderboardMenu.leaderboard.push_back(tmpItem);
        }
    }

    void InitLeaderboardMenu(Game& game)
    {
        LeaderboardMenu& leaderboardMenu = game.GUI.leaderboardMenu;

        InitText(leaderboardMenu.heading, L"Таблица рекордов", game.assets.font, TEXT_HEADING_1);

        leaderboardMenu.heading.setStyle(sf::Text::Bold);
        leaderboardMenu.heading.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);

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
