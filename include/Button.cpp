#include "Button.hpp"

Button::Button() {

}

Button::Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColor) {
    text.setString(t);
    text.setFillColor(textColor);
    text.setCharacterSize(charSize);
    button.setSize(size);
    button.setFillColor(bgColor);
}

void Button::setFont(sf::Font &font) {
    text.setFont(font);
}

void Button::setBgColor(sf::Color color) {
    button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
    text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f pos) {
    button.setPosition(pos);
    float xPos = (pos.x + button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2);
    float yPos = (pos.y + button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 2);
    text.setPosition({xPos, yPos - 3});
}

void Button::drawTo(sf::RenderWindow &window) {
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow &window) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;
    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;
    float btnxPosWidth = btnPosX + button.getLocalBounds().width;
    float btnyPosHeight = btnPosY + button.getLocalBounds().height;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    } else {
        return false;
    }
}

std::string Button::getText() {
    return text.getString();
}