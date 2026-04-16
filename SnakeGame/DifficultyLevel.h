#pragma once
#include <map>
#include "Shared/Constants.h"

namespace SnakeGame
{
    enum class DifficultyLevelType
    {
        Easy = 0,
        EasyMedium,
        Medium,
        MediumHard,
        Hard
    };

    struct DifficultLevelConfig
    {
        float snakeSpeed;
        unsigned pointsPerApple;
    };

    extern const std::map<DifficultyLevelType, DifficultLevelConfig> LEVEL_CONFIG;

    struct DifficultyLevel
    {
        DifficultyLevelType type;
        DifficultLevelConfig value;
    };
}
