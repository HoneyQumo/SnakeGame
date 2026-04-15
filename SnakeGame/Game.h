#pragma once
#include <stack>
#include "Field.h"
#include "GUI/GUI.h"
#include "Shared/Constants.h"
#include "Snake/Snake.h"

namespace SnakeGame
{
    enum class GameState
    {
        Playing = 0,
        Pause,
        MainMenu,
        DifficultyLevel,
        Settings,
        Leaderboard,
    };

    struct Game
    {
        sf::Font font;

        GUI GUI;

        Field field;
        Snake snake;
        std::stack<GameState> gameStateStack;
    };

    void ResetGameState(Game& game);
    void PushGameState(Game& game, const GameState& state);
    void PopGameState(Game& game);
    void SwitchGameState(Game& game, const GameState& state);
    GameState GetCurrentGameState(const Game& game);

    void ResetGame(Game& game);
    void InitGame(Game& game);
    void UpdateGame(Game& game, const float& deltaTime);
    void DrawGame(sf::RenderWindow& window, const Game& game);
}
