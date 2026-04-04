#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"

const std::string RESOURCES_PATH = "Resources/";

int main()
{
    using namespace SnakeGame;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake Game by HoneyQumo");

    Game game;
    InitField(game.field);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (unsigned x = 0; x < NUMBER_CELLS; ++x)
        {
            for (unsigned y = 0; y < NUMBER_CELLS; ++y)
            {
                window.draw(game.field.cells[x][y].shape);
            }
        }


        window.display();
    }

    return 0;
}
