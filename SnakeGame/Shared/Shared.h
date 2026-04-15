#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "Direction.h"

namespace SnakeGame
{
    struct MenuOption
    {
        std::string title;
        sf::Text textNode;
    };

    struct Shared
    {
    };
}
