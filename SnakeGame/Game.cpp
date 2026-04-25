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

        /* GUI */
        InitMainMenu(game);
        InitPauseMenu(game);
        InitDifficultyLevelMenu(game);
        InitHUD(game);
        InitGameOverMenu(game);
        InitLeaderboardMenu(game);
        InitAskNicknameMenu(game);

        /*Sounds*/
        game.assets.music.setPlayingOffset(sf::seconds(0.f));
        game.assets.music.setLoop(true);
        game.assets.music.play();

        /* Game Instances */
        InitField(game.field);
        InitSnake(game.snake, game.assets);

        game.score = 0;
        game.apples.clear();
        SpawnApple(game);
    }

    void InitGame(Game& game)
    {
        /* Fonts */
        assert(game.assets.font.loadFromFile(RESOURCES_FONTS + "\\pixel_font-7.ttf"));

        /* Graphics */
        assert(game.assets.snakeHead.loadFromFile(RESOURCES_GRAPHICS + "\\head_right.png"));
        assert(game.assets.snakeBody.loadFromFile(RESOURCES_GRAPHICS + "\\body_horizontal.png"));
        assert(game.assets.snakeBodyAngle.loadFromFile(RESOURCES_GRAPHICS + "\\body_bottomright.png"));
        assert(game.assets.snakeTail.loadFromFile(RESOURCES_GRAPHICS + "\\tail_left.png"));
        assert(game.assets.apple.loadFromFile(RESOURCES_GRAPHICS + "\\apple.png"));

        /* Sounds */
        assert(game.assets.musicBuffer.loadFromFile(RESOURCES_AUDIO + "\\music.wav"));
        game.assets.music.setBuffer(game.assets.musicBuffer);
        game.assets.music.setVolume(MUSIC_INITIAL_VOLUME);

        assert(game.assets.deathBuffer.loadFromFile(RESOURCES_AUDIO + "\\death.wav"));
        game.assets.death.setBuffer(game.assets.deathBuffer);
        game.assets.death.setVolume(GENERAL_INITIAL_VOLUME);

        assert(game.assets.eatBuffer.loadFromFile(RESOURCES_AUDIO + "\\eat.wav"));
        game.assets.eat.setBuffer(game.assets.eatBuffer);
        game.assets.eat.setVolume(GENERAL_INITIAL_VOLUME);

        assert(game.assets.menuToggleBuffer.loadFromFile(RESOURCES_AUDIO + "\\menu-toggle.wav"));
        game.assets.menuToggle.setBuffer(game.assets.menuToggleBuffer);
        game.assets.menuToggle.setVolume(GENERAL_INITIAL_VOLUME);

        assert(game.assets.menuSelectBuffer.loadFromFile(RESOURCES_AUDIO + "\\menu-select.wav"));
        game.assets.menuSelect.setBuffer(game.assets.menuSelectBuffer);
        game.assets.menuSelect.setVolume(GENERAL_INITIAL_VOLUME);


        game.difficulty = {DifficultyLevelType::Medium, LEVEL_CONFIG.at(DifficultyLevelType::Medium)};

        DeserializeAndLoadLeaderboard(game.leaderboard);

        ResetGame(game);
    }


    void UpdateGame(Game& game, const float& deltaTime)
    {
        const auto& gameState = GetCurrentGameState(game);
        const float computedDistance = game.difficulty.value.snakeSpeed * deltaTime;

        switch (gameState)
        {
        case GameState::MainMenu:
            break;
        case GameState::Playing:

            SnakeControl(game.snake);
            UpdateSnake(game.snake, computedDistance);

            if (HasSnakeCollisionWithWall(game.snake.segments[0], game.field) || HasSnakeCollisionWithSelf(game.snake))
            {
                game.assets.music.stop();
                game.assets.death.play();
                PushGameState(game, GameState::GameOver);

                if (game.score > 0 && (game.leaderboard.array.empty() || game.score > std::prev(game.leaderboard.array.end())->score))
                {
                    PushGameState(game, GameState::AskNickname);
                }

                break;
            }

            for (unsigned int i = 0; i < game.apples.size(); ++i)
            {
                if (IsRectangleCollide(
                    game.snake.segments[0].sprite.getPosition(), {CELL_WIDTH, CELL_HEIGHT},
                    game.apples[i].sprite.getPosition(), {APPLE_SIZE, APPLE_SIZE}
                ))
                {
                    game.assets.eat.play();
                    game.score += game.difficulty.value.pointsPerApple;
                    GrowSnake(game.snake, game.assets);
                    game.apples.clear();
                    SpawnApple(game);
                }
            }

            UpdateHUD(game);

            break;

        case GameState::GameOver:
            UpdateGameOverMenu(game);

            break;
        case GameState::Pause:
        case GameState::DifficultyLevel:
        case GameState::Settings:
        case GameState::Leaderboard:
            break;
        }
    }

    void DrawGame(sf::RenderWindow& window, const sf::View& HUDView, const Game& game)
    {
        const auto& gameState = GetCurrentGameState(game);

        switch (gameState)
        {
        case GameState::MainMenu:
            DrawMainMenu(window, game.GUI.mainMenu);

            break;
        case GameState::Playing:
            DrawField(window, game.field);
            DrawApples(window, game.apples);
            DrawSnake(window, game.snake);
            // DrawTurnPointSprite(window, game.snake);

            window.setView(HUDView);
            DrawHUD(window, game.GUI.HUD);

            break;

        case GameState::AskNickname:
            DrawAskNicknameMenu(window, game.GUI.askNicknameMenu);

            break;
        case GameState::GameOver:
            DrawGameOverMenu(window, game.GUI.gameOverMenu);

            break;
        case GameState::Pause:
            // if (game.GUI.pauseMenu.heading.getString().isEmpty())
            // {
            //     InitPauseMenu(game);
            // }

            DrawPauseMenu(window, game.GUI.pauseMenu);

            break;
        case GameState::DifficultyLevel:
            DrawDifficultyLevelMenu(window, game.GUI.difficultyLevelMenu);

            break;
        case GameState::Settings:
            break;
        case GameState::Leaderboard:
            DrawLeaderboardMenu(window, game.GUI.leaderboardMenu);
            break;
        }
    }
}
