#pragma once
#include <string>
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
    /* Paths */
    const std::string RESOURCES_PATH = "Resources/";
    const std::string RESOURCES_AUDIO = RESOURCES_PATH + "Audio";
    const std::string RESOURCES_FONTS = RESOURCES_PATH + "Fonts";
    const std::string RESOURCES_GRAPHICS = RESOURCES_PATH + "Graphics";

    /* Video */
    constexpr unsigned SCREEN_WIDTH = 1000;
    constexpr unsigned SCREEN_HEIGHT = 1000;
    // constexpr float SCREEN_PADDING = 10.f;
    constexpr float OFFSET_TOP_WINDOW_10_PERCENT = (SCREEN_HEIGHT / 100.f) * 10.f;
    constexpr float OFFSET_TOP_WINDOW_20_PERCENT = (SCREEN_HEIGHT / 100.f) * 20.f;

    constexpr float HUD_BACKGROUND_HEIGHT = 50.f;
    constexpr float HUD_VIEW_PERCENT = HUD_BACKGROUND_HEIGHT / SCREEN_HEIGHT;
    constexpr float DEFAULT_VIEW_PERCENT = 1.f - HUD_VIEW_PERCENT;

    /* Audio */
    // constexpr float INITIAL_VOLUME = 25.f;

    /* General */
    // constexpr unsigned int TIMEOUT_BEFORE_RESTART_IN_SECONDS = 2;
    constexpr float EPSILON = 0.01f;

    /* Field */
    constexpr unsigned NUMBER_CELLS = 20;
    constexpr unsigned CELL_WIDTH = SCREEN_WIDTH / NUMBER_CELLS;
    constexpr unsigned CELL_HEIGHT = SCREEN_HEIGHT / NUMBER_CELLS;
    constexpr float AVERAGE_CELL_SIZE = (CELL_WIDTH + CELL_HEIGHT) / 2.f;
    constexpr float APPLE_SIZE = 40.f;

    const auto LIGHT_GREEN_COLOR = sf::Color(170, 215, 81, 255);
    const auto DARK_GREEN_COLOR = sf::Color(162, 209, 73, 255);
    const auto GRAY_COLOR = sf::Color(100, 100, 100, 255);

    /* HUD */
    const auto HUD_BACKGROUND_COLOR = sf::Color(87, 138, 28, 255);

    /* Text */
    constexpr unsigned TEXT_HEADING_1 = 60;
    constexpr unsigned TEXT_HEADING_2 = 50;
    constexpr unsigned TEXT_HEADING_3 = 40;
    constexpr unsigned TEXT_MENU_ITEM = 30;
}
