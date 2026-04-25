#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main()
{
    using namespace SnakeGame;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game by HoneyQumo");

    sf::View defaultView(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    sf::View HUDView(sf::FloatRect(0, 0, SCREEN_WIDTH, HUD_BACKGROUND_HEIGHT));

    defaultView.setViewport(sf::FloatRect(0.f, HUD_VIEW_PERCENT, 1.f, DEFAULT_VIEW_PERCENT));
    HUDView.setViewport(sf::FloatRect(0.f, 0.0f, 1.f, HUD_VIEW_PERCENT));

    Game game;
    InitGame(game);

    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                const auto& gameState = GetCurrentGameState(game);

                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    switch (gameState)
                    {
                    case GameState::MainMenu:
                        window.close();
                        break;
                    case GameState::Playing:
                        ResetPauseMenu(game.GUI.pauseMenu);
                        PushGameState(game, GameState::Pause);
                        break;
                    case GameState::Pause:
                        PopGameState(game);
                        break;
                    default:
                        PopGameState(game);
                        break;
                    }
                    break;

                case sf::Keyboard::Backspace:
                    if (gameState != GameState::AskNickname)
                    {
                        PopGameState(game);
                    }

                    break;

                case sf::Keyboard::P:
                    switch (gameState)
                    {
                    case GameState::Playing:
                        ResetPauseMenu(game.GUI.pauseMenu);
                        PushGameState(game, GameState::Pause);
                        break;
                    case GameState::Pause:
                        PopGameState(game);
                        break;
                    }
                    break;
                }
            }


            const auto& gameState = GetCurrentGameState(game);
            switch (gameState)
            {
            case GameState::Playing:
                break;
            case GameState::GameOver:
                GameOverMenuKeyboardHandler(event, game);
                break;
            case GameState::AskNickname:
                AskNicknameMenuKeyboardHandler(event, game);
                break;
            case GameState::Pause:
                PauseMenuKeyboardHandler(event, game);
                break;
            case GameState::MainMenu:
                MainMenuKeyboardHandler(window, event, game);
                break;
            case GameState::DifficultyLevel:
                DifficultyLevelMenuKeyboardHandler(event, game);
                break;
            case GameState::Settings:
            case GameState::Leaderboard:
                break;
            }
        }

        UpdateGame(game, deltaTime);

        window.clear();

        window.setView(defaultView);
        DrawGame(window, HUDView, game);

        window.display();
    }

    return 0;
}
