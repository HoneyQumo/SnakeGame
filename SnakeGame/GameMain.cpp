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
    float movementTimer = 0.f;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    while (window.isOpen())
    {
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        movementTimer += deltaTime;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        UpdateGame(game, movementTimer);

        window.clear();
        DrawGame(window, game);
        window.display();
    }

    return 0;
}
