#pragma once
#include "MainMenu.h"
#include "PauseMenu.h"
#include "DifficultyLevelMenu.h"
#include "GameOverMenu.h"
#include "HUD.h"
#include "LeaderboardMenu.h"

namespace SnakeGame
{
    struct GUI
    {
        MainMenu mainMenu;
        PauseMenu pauseMenu;
        DifficultyLevelMenu difficultyLevelMenu;
        HUD HUD;
        GameOverMenu gameOverMenu;
        LeaderboardMenu leaderboardMenu;
    };
}
