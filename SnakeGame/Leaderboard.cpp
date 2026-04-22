#include <fstream>
#include <algorithm>
#include "Leaderboard.h"
#include "Game.h"

namespace SnakeGame
{
    void AddItemToLeaderboard(Game& game)
    {
        auto& leaderboard = game.leaderboard.array;
        leaderboard.push_back({L"XYZ", game.score});

        std::stable_sort(leaderboard.begin(), leaderboard.end(), [](const LeaderboardItem& item1, const LeaderboardItem& item2)
        {
            return item1.score > item2.score;
        });

        if (leaderboard.size() > 10)
        {
            leaderboard.erase(leaderboard.end());
        }
    }

    std::vector<LeaderboardItem> GetSortedLeaderboard(std::vector<LeaderboardItem> leaderboard)
    {
        std::stable_sort(leaderboard.begin(), leaderboard.end(), [](const LeaderboardItem& item1, const LeaderboardItem& item2)
        {
            return item1.score > item2.score;
        });

        return leaderboard;
    }

    bool SerializeAndSaveGame(const Leaderboard& leaderboard)
    {
        std::wofstream file(LEADERBOARD_FILE_PATH);

        if (file.is_open())
        {
            for (const auto& item : leaderboard.array)
            {
                file << item.playerName << L" " << item.score << "\n";
            }

            file.close();
            return true;
        }

        return false;
    }

    bool DeserializeAndLoadLeaderboard(Leaderboard& leaderboard)
    {
        std::wifstream file(LEADERBOARD_FILE_PATH);

        if (file.is_open())
        {
            leaderboard.array.clear();
            LeaderboardItem tmpItem;

            while (file >> tmpItem.playerName >> tmpItem.score)
            {
                leaderboard.array.push_back(tmpItem);
            }

            file.close();
            return true;
        }
        
        return false;
    }
}
