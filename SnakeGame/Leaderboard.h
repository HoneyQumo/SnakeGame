#pragma once
#include <string>
#include <vector>

namespace SnakeGame
{
    struct LeaderboardItem
    {
        std::wstring playerName;
        unsigned score;
    };

    struct Leaderboard
    {
        std::vector<LeaderboardItem> array;
    };

    struct Game;
    void AddItemToLeaderboard(Game& game);
    std::vector<LeaderboardItem> GetSortedLeaderboard(std::vector<LeaderboardItem> leaderboard);

    bool SerializeAndSaveGame(const Leaderboard& leaderboard);
    bool DeserializeAndLoadLeaderboard(Leaderboard& leaderboard);
    bool ClearLeaderboard(Game& game);
}
