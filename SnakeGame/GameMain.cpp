#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main()
{
    using namespace SnakeGame;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game by HoneyQumo");

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

            if (GetCurrentGameState(game) == GameState::MainMenu)
            {
                MainMenuKeyboardHandler(window, event, game);
            }
            // else if (GetCurrentGameState(game) == GameState::Settings)
            // {
            //     SettingsKeyboardHandler(event, game);
            // }
            else if (GetCurrentGameState(game) == GameState::Pause)
            {
                PauseMenuKeyboardHandler(event, game);
            }
        }

        UpdateGame(game, deltaTime);

        window.clear();
        DrawGame(window, game);
        window.display();
    }

    return 0;
}
