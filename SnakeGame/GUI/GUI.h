#pragma once
#include "AskNicknameMenu.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "DifficultyLevelMenu.h"
#include "GameOverMenu.h"
#include "HUD.h"
#include "LeaderboardMenu.h"
#include "SettingsMenu.h"

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
        AskNicknameMenu askNicknameMenu;
        SettingsMenu settingsMenu;
    };
}
