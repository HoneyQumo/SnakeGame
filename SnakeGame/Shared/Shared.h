#pragma once
#include <string>
#include "SFML/Graphics.hpp"
#include "Direction.h"
#include "Math.h"

namespace SnakeGame
{
    struct MenuOption
    {
        std::wstring title;
        sf::Text textNode;
    };

    // struct Shared
    // {
    // };

    void InitText(
        sf::Text& node,
        const sf::String& text,
        const sf::Font& font,
        unsigned textSize = TEXT_HEADING_1,
        sf::Color color = sf::Color::White,
        sf::Vector2f origin = {0.5f, 0.5f}
    );

    template <typename T>
    static void MenuToggleOption(std::map<T, MenuOption>& options, T& selectedOptionKey, DirectionVertical direction)
    {
        if (options.empty()) return;

        const auto it = options.find(selectedOptionKey);
        if (it == options.end()) return;

        if (direction == DirectionVertical::Up)
        {
            if (it == options.begin())
            {
                auto prevIt = std::prev(options.end());
                selectedOptionKey = prevIt->first;
                prevIt->second.textNode.setFillColor(sf::Color::Green);
            }
            else
            {
                auto prevIt = std::prev(it);
                selectedOptionKey = prevIt->first;
                prevIt->second.textNode.setFillColor(sf::Color::Green);
            }
        }
        else if (direction == DirectionVertical::Down)
        {
            const auto nextIt = std::next(it);
            if (nextIt == options.end())
            {
                auto nextIt = options.begin();
                selectedOptionKey = nextIt->first;
                nextIt->second.textNode.setFillColor(sf::Color::Green);
            }
            else
            {
                selectedOptionKey = nextIt->first;
                nextIt->second.textNode.setFillColor(sf::Color::Green);
            }
        }

        it->second.textNode.setFillColor(sf::Color::White);
    }

    template <typename TOptions, typename TKey>
    static void SetOptionKey(TOptions& options, TKey& oldKey, const TKey& newKey)
    {
        if (options.empty()) return;

        const auto it = options.find(newKey);
        if (it == options.end()) return;

        oldKey = newKey;
        for (auto& option : options)
        {
            option.second.textNode.setFillColor(option.first == newKey ? sf::Color::Green : sf::Color::White);
        }
    }
}
