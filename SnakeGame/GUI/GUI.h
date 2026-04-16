#pragma once
#include "MainMenu.h"
#include "PauseMenu.h"
#include "DifficultyLevelMenu.h"

namespace SnakeGame
{
    struct GUI
    {
        MainMenu mainMenu;
        PauseMenu pauseMenu;
        DifficultyLevelMenu difficultyLevelMenu;
    };
}
