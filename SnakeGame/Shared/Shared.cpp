#include "Shared.h"

namespace SnakeGame
{
    void InitText(
        sf::Text& node,
        const sf::String& text,
        const sf::Font& font,
        const unsigned textSize,
        const sf::Color color,
        const sf::Vector2f origin
    )
    {
        node.setString(text);
        node.setFont(font);
        node.setCharacterSize(textSize);
        node.setFillColor(color);
        node.setOrigin(GetTextOrigin(node, origin));
    }
}
