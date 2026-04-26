#pragma once
#include <stack>
#include "Apple.h"
#include "Field.h"
#include "DifficultyLevel.h"
#include "Leaderboard.h"
#include "GUI/GUI.h"
#include "Shared/Assets.h"
#include "Shared/Constants.h"
#include "Snake/Snake.h"

namespace SnakeGame
{
    enum class GameState
    {
        Playing = 0,
        GameOver,
        Pause,
        MainMenu,
        DifficultyLevel,
        Settings,
        Leaderboard,
        AskNickname
    };

    struct Game
    {
        Assets assets;

        GUI GUI;

        Field field;
        Snake snake;
        std::vector<Apple> apples;

        unsigned score = 0;

        DifficultyLevel difficulty;
/
        Settings settings;

        std::stack<GameState> gameStateStack;
        Leaderboard leaderboard;
    };

    void ResetGameState(Game& game);
    void PushGameState(Game& game, const GameState& state);
    void PopGameState(Game& game);
    void SwitchGameState(Game& game, const GameState& state);
    GameState GetCurrentGameState(const Game& game);

    void ResetGame(Game& game);
    void InitGame(Game& game);
    void UpdateGame(Game& game, const float& deltaTime);
    void DrawGame(sf::RenderWindow& window, const sf::View& HUDView, const Game& game);
}
