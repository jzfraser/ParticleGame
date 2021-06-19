#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.hpp"

class Button {
public:
    Button();
    Button(std::string t, sf::Vector2f size, int charSize,
        sf::Color bgColor, sf::Color textColor, ParticleType pt);
    void setFont(sf::Font &font);
    void setBgColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setPosition(sf::Vector2f pos);
    void setType(ParticleType pT);
    ParticleType getType();
    void drawTo(sf::RenderWindow &window);
    bool isMouseOver(sf::RenderWindow &window);

private:
    sf::RectangleShape button;
    sf::Text text;
    ParticleType pType;
};