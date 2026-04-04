#pragma once
#include "SFML/Graphics.hpp"
#include <string>

namespace SnakeGame
{
    /* Paths */
    const std::string RESOURCES_PATH = "Resources/";
    const std::string RESOURCES_AUDIO = RESOURCES_PATH + "Audio";
    const std::string RESOURCES_FONTS = RESOURCES_PATH + "Fonts";
    const std::string RESOURCES_GRAPHICS = RESOURCES_PATH + "Graphics";

    /* Video */
    constexpr unsigned int SCREEN_WIDTH = 800;
    constexpr unsigned int SCREEN_HEIGHT = 800;
    constexpr float SCREEN_PADDING = 10.f;
    constexpr float OFFSET_TOP_WINDOW_10_PERCENT = (SCREEN_HEIGHT / 100.f) * 10.f;
    constexpr float OFFSET_TOP_WINDOW_20_PERCENT = (SCREEN_HEIGHT / 100.f) * 20.f;

    /* Audio */
    constexpr float INITIAL_VOLUME = 25.f;

    /* General */
    constexpr unsigned int TIMEOUT_BEFORE_RESTART_IN_SECONDS = 2;

    /* Field */
    constexpr unsigned NUMBER_CELLS = 20;
    constexpr unsigned CELL_WIDTH = SCREEN_WIDTH / NUMBER_CELLS;
    constexpr unsigned CELL_HEIGHT = SCREEN_HEIGHT / NUMBER_CELLS;
    const auto LIGHT_GREEN_COLOR = sf::Color(170, 215, 81, 255);
    const auto DARK_GREEN_COLOR = sf::Color(162, 209, 73, 255);
}
