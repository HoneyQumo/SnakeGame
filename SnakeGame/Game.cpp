#include <cassert>
#include "Game.h"

namespace SnakeGame
{
    void ResetGameState(Game& game)
    {
        SwitchGameState(game, GameState::MainMenu);
    }

    void PushGameState(Game& game, const GameState& state)
    {
        game.gameStateStack.push(state);
    }

    void PopGameState(Game& game)
    {
        if (game.gameStateStack.size() != 1)
        {
            game.gameStateStack.pop();
        }
    }

    void SwitchGameState(Game& game, const GameState& state)
    {
        while (!game.gameStateStack.empty())
        {
            game.gameStateStack.pop();
        }

        PushGameState(game, state);
    }

    GameState GetCurrentGameState(const Game& game)
    {
        if (!game.gameStateStack.empty())
        {
            return game.gameStateStack.top();
        }

        return GameState::MainMenu;
    }

    void ResetGame(Game& game)
    {
        ResetGameState(game);

        InitMainMenu(game);
        InitPauseMenu(game);

        InitField(game.field);
        InitSnake(game.snake);
    }

    void InitGame(Game& game)
    {
        /* Fonts */
        assert(game.font.loadFromFile(RESOURCES_FONTS + "\\AtariTetrisArcade-Regular.otf"));

        /* Graphics */
        assert(game.snake.headTexture.loadFromFile(RESOURCES_GRAPHICS + "\\head_right.png"));
        assert(game.snake.bodyTexture.loadFromFile(RESOURCES_GRAPHICS + "\\body_horizontal.png"));
        assert(game.snake.bodyAngleTexture.loadFromFile(RESOURCES_GRAPHICS + "\\body_bottomright.png"));
        assert(game.snake.tailTexture.loadFromFile(RESOURCES_GRAPHICS + "\\tail_left.png"));

        ResetGame(game);
    }


    void UpdateGame(Game& game, const float& deltaTime)
    {
        const auto& gameState = GetCurrentGameState(game);

        switch (gameState)
        {
        case GameState::MainMenu:
            break;
        case GameState::Playing:
            SnakeControl(game.snake);
            UpdateSnake(game.snake, deltaTime);

            break;

        case GameState::Pause:
        case GameState::DifficultyLevel:
        case GameState::Settings:
        case GameState::Leaderboard:
            break;
        }
    }

    void DrawGame(sf::RenderWindow& window, const Game& game)
    {
        const auto& gameState = GetCurrentGameState(game);

        switch (gameState)
        {
        case GameState::MainMenu:
            DrawMainMenu(window, game.GUI.mainMenu);

            break;
        case GameState::Playing:
            DrawField(window, game.field);
            DrawSnake(window, game.snake);
            DrawTurnPointSprite(window, game.snake);
            break;

        case GameState::Pause:
            // if (game.GUI.pauseMenu.heading.getString().isEmpty())
            // {
            //     InitPauseMenu(game);
            // }
            
            DrawPauseMenu(window, game.GUI.pauseMenu);

            break;
        case GameState::DifficultyLevel:
        case GameState::Settings:
        case GameState::Leaderboard:
            break;
        }
    }
}
