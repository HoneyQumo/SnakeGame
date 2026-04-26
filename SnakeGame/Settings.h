#pragma once
#include <map>

namespace SnakeGame
{
    enum class SettingsType
    {
        Sound = 0,
        Music,
        ResetLeaderboard,
    };


    struct Settings
    {
        std::map<SettingsType, bool> states = {
            {SettingsType::Sound, true},
            {SettingsType::Music, true},
        };
    };
}
