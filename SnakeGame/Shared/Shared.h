#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "Direction.h"

namespace SnakeGame
{

    struct MenuOption
    {
        std::wstring title;
        sf::Text textNode;
    };

    struct Shared
    {
    };
}
