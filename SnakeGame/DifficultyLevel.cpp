#include "DifficultyLevel.h"

namespace SnakeGame
{
    const std::map<DifficultyLevelType, DifficultLevelConfig> LEVEL_CONFIG = {
        {DifficultyLevelType::Easy, {3 * AVERAGE_CELL_SIZE, 2}},
        {DifficultyLevelType::EasyMedium, {5 * AVERAGE_CELL_SIZE, 4}},
        {DifficultyLevelType::Medium, {8 * AVERAGE_CELL_SIZE, 6}},
        {DifficultyLevelType::MediumHard, {11 * AVERAGE_CELL_SIZE, 8}},
        {DifficultyLevelType::Hard, {14 * AVERAGE_CELL_SIZE, 10}},
    };
}
