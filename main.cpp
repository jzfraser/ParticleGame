#include "src/Button.hpp"
#include "src/Constants.hpp"
#include "src/ParticleGrid.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

void spawnParticles(ParticleGrid* world, ParticleType t, int x, int y) {
    int col      = x / PARTICLE_WIDTH;
    int row      = y / PARTICLE_HEIGHT;
    float radius = 50.0;
    for (uint16_t i = 0; i < 100; i++) {
        float ran   = rand() % 100 / 100.f;
        float r     = radius * sqrtf(ran);
        float theta = rand() % 100 / 100.f * 2.f * M_PI;
        float rx    = cos(theta) * r;
        float ry    = sin(theta) * r;
        int32_t mpx = std::clamp(col + rx, 0.f, WORLD_WIDTH - 1.f);
        int32_t mpy = std::clamp(row + ry, 0.f, WORLD_HEIGHT - 1.f);
        world->createP(t, mpy, mpx);
    }
}

void createButtons(Button* btns, sf::Font& font) {
    btns[0] = Button("Sand", { 80, 55 }, 25, sf::Color::White, sf::Color::Black, SAND);
    btns[0].setFont(font);
    btns[0].setPosition({ WIN_WIDTH - 90, 10 });
    btns[1] = Button("Water", { 80, 55 }, 25, sf::Color::White, sf::Color::Black, WATER);
    btns[1].setFont(font);
    btns[1].setPosition({ WIN_WIDTH - 90, 70 });
    btns[2] = Button("Wood", { 80, 55 }, 25, sf::Color::White, sf::Color::Black, WOOD);
    btns[2].setFont(font);
    btns[2].setPosition({ WIN_WIDTH - 90, 130 });
    btns[3] = Button("Fire", { 80, 55 }, 25, sf::Color::White, sf::Color::Black, FIRE);
    btns[3].setFont(font);
    btns[3].setPosition({ WIN_WIDTH - 90, 190 });
}

void drawButtons(Button* btns, sf::RenderWindow& window) {
    for (int i = 0; i < 4; i++) {
        btns[i].drawTo(window);
    }
}

int mouseOverButton(Button* btns, sf::RenderWindow& window) {
    for (int i = 0; i < 4; i++) {
        if (btns[i].isMouseOver(window))
            return i;
    }
    return -1;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Particle Game");
    window.setFramerateLimit(144);
    sf::Clock deltaClock;
    sf::Font droidSansMono;
    droidSansMono.loadFromFile("../include/DroidSansMono.ttf");

    ParticleGrid world = ParticleGrid(WORLD_WIDTH, WORLD_HEIGHT);

    bool spawning          = false;
    ParticleType spawnType = EMPTY;
    Button btns[4];
    createButtons(btns, droidSansMono);

    while (window.isOpen()) {
        // float dt = deltaClock.restart().asSeconds();
        // int fps  = 1 / dt;
        // std::cout << fps << "\n";
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                int btnNum = mouseOverButton(btns, window);
                if (btnNum >= 0) {
                    spawnType = btns[btnNum].getType();
                } else {
                    spawning = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
                spawning = false;
        }
        if (spawning) {
            int x = sf::Mouse::getPosition(window).x;
            int y = sf::Mouse::getPosition(window).y;
            spawnParticles(&world, spawnType, x, y);
        }

        world.update();
        window.clear();
        window.draw(world);
        drawButtons(btns, window);
        window.display();
    }

    return 0;
}
