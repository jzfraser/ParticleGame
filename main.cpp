#include "src/Button.hpp"
#include "src/Constants.hpp"
#include "src/ParticleGrid.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

double spawn_radius = 50.f;

void spawnParticles(ParticleGrid* world, ParticleType t, int x, int y) {
    int col = x / PARTICLE_WIDTH;
    int row = y / PARTICLE_HEIGHT;

    uint16_t iters = t == WOOD ? spawn_radius * 50.f : spawn_radius * 3.f;
    for (uint16_t i = 0; i < iters; i++) {
        float ran   = rand() % 100 / 100.f;
        float r     = spawn_radius * sqrtf(ran);
        float theta = rand() % 100 / 100.f * 2.f * M_PI;
        float rx    = cos(theta) * r; // random x inside radius
        float ry    = sin(theta) * r; // random y inside radius
        // clamp to keep random point inside of world bounds
        int32_t mpx = std::clamp(col + rx, 0.f, WORLD_WIDTH - 1.f);
        int32_t mpy = std::clamp(row + ry, 0.f, WORLD_HEIGHT - 1.f);
        world->createP(t, mpy, mpx);
    }
    // world->createP(t, row, col);
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
    window.setFramerateLimit(60);
    sf::Clock deltaClock;
    sf::Font droidSansMono;
    droidSansMono.loadFromFile("../include/DroidSansMono.ttf");

    ParticleGrid world = ParticleGrid(WORLD_WIDTH, WORLD_HEIGHT);

    bool spawning          = false;
    ParticleType spawnType = SAND;
    Button btns[4];
    createButtons(btns, droidSansMono);
    sf::CircleShape spawnArea(spawn_radius);
    spawnArea.setOutlineThickness(1.f);
    spawnArea.setOutlineColor(sf::Color(255, 255, 255, 60));
    spawnArea.setFillColor(sf::Color(0, 0, 0, 0));

    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();
        // int fps  = 1 / dt;
        // std::cout << fps << "\n";


        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;
        spawnArea.setPosition(mouseX - spawn_radius, mouseY - spawn_radius);

        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::C)
                    world.clearParticles();
                break;
            case sf::Event::MouseWheelScrolled: {
                if (event.type == sf::Event::MouseWheelScrolled &&
                    event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    int delta = event.mouseWheelScroll.delta;
                    spawn_radius = std::clamp(spawn_radius + (delta % 10), 1.0, 200.0);
                    spawnArea.setRadius(spawn_radius);
                }
                break;
            }
            case sf::Event::MouseButtonPressed: {
                int btnNum = mouseOverButton(btns, window);
                if (btnNum >= 0) {
                    spawnType = btns[btnNum].getType();
                } else {
                    spawning = true;
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
                spawning = false;
                break;
            default:
                break;
            }
        }

        if (spawning) {
            int x = sf::Mouse::getPosition(window).x;
            int y = sf::Mouse::getPosition(window).y;
            spawnParticles(&world, spawnType, x, y);
        }

        world.readyParticles();
        world.update(dt);
        window.clear();
        window.draw(world);
        window.draw(spawnArea);
        drawButtons(btns, window);
        window.display();
    }

    return 0;
}
